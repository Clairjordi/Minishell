/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:01:37 by clorcery          #+#    #+#             */
/*   Updated: 2022/10/05 16:18:10 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_verif_if_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\"')
	{
		if (str[i + 1] == '\"' && str[i + 2] == '\0')
		{
			ft_putendl_fd("Command not found", 2);
			return (-1);
		}
	}
	else if (str[i] == '\'')
	{
		if (str[i + 1] == '\'' && str[i + 2] == '\0')
		{
			ft_putendl_fd("Command not found", 2);
			return (-1);
		}
	}
	return (0);
}

int	ft_verif_parsing(char *str, t_shell *shell)
{
	if (ft_verif_if_str(str) == -1)
		return (-1);
	if (ft_count_quote(str) == -1)
		return (-1);
	if (ft_verif_pipe(shell, str) == -1)
		return (-1);
	if (ft_verif_redirect(str) == -1)
		return (-1);
	return (0);
}

void	*ft_free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

int		ft_check_dollar(char c)
{
	if (c == '$')
		return (1);
	return (0);
}

char	*ft_cdup(char c)
{
	char	*dest;

	dest = malloc(sizeof(char) * 2);
	if (!dest)
		return (NULL);
	dest[0] = c;
	dest[1] = '\0';
	return (dest);
}

char	*ft_charjoin(char *s1, char c)
{
	char	*result;
	int		len;
	int		i;

	result = NULL;
	if (!s1 && !c)
		return (NULL);
	else if (!s1)
	{
		result = ft_cdup(c);
		return (result);
	}
	len = ft_strlen(s1);
	result = malloc(sizeof(char*) * len + 2);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = c;
	i++;
	result[i] = '\0';
	free(s1);
	return (result);
}

int	ft_open_quote(t_shell *shell, char c)
{
	if (c == '\"')
	{
		if (shell->quote == 2)
			shell->quote = 0;
		else if (shell->quote == 1)
			shell->quote = 1;
		else
			shell->quote = 2;
	}
	else if (c == '\'')
	{
		if (shell->quote == 1)
			shell->quote = 0;
		else if (shell->quote == 2)
			shell->quote = 2;
		else
			shell->quote = 1;
	}
	return (shell->quote);
}

char	*ft_rep(char *s, t_shell *shell, int i, int j)
{
	char	*new;

	new = s;
	shell->quote = ft_open_quote(shell, shell->arg->value_split[i][j]);
	if (!(shell->arg->value_split[i][j] == '\'' && shell->quote != 2)
				&& !(shell->arg->value_split[i][j] == '\"' && shell->quote != 1))
		new = ft_charjoin(s, shell->arg->value_split[i][j]);
	else
		return (s);
	return (new);
}

int	ft_replace_value(t_shell *shell, char **envp)
{
	//int		dollar;
	int		i;
	int		j;
	char	*tmp;
	(void)envp;

	//dollar = 0;
	while (shell->arg != NULL)
	{
		i = 0;
		while (shell->arg->value_split[i] != NULL)
		{
			j = 0;
			tmp = NULL;
			while (shell->arg->value_split[i][j])
			{
				/* dollar = ft_check_dollar(shell->arg->value[i]); */
				/* if (dollar == 1) */
				/* 	tmp = ft_rep_if_dollar(tmp, shell, envp, i); */
				/* else */
					tmp = ft_rep(tmp, shell, i, j);
				j++;
			}
			if (tmp != NULL)
			{
				shell->arg->value_split[i] = ft_free_ptr(shell->arg->value_split[i]);
				shell->arg->value_split[i] = tmp;
				ft_printf("{%s}\n", shell->arg->value_split[i]);
			}
			i++;
		}
		shell->arg = shell->arg->next;
	}
	return (0);
}

int		ft_parsing_bis(t_shell *shell, char **envp)
{
	if (ft_replace_value(shell, envp) == -1)
		return (-1);
	return (0);
}

void	ft_parsing(char *str, t_shell *shell, char **envp)
{
	if (ft_verif_parsing(str, shell) == -1)
		return ;
	if (shell->argc == 1)
	{
		shell->tab_cmd = ft_split_value(str, ' ');
		if (shell->tab_cmd == NULL)
			ft_free_malloc(shell);
	}
	else
	{
		shell->tab_cmd = ft_split_pipes(str, '|');
		if (shell->tab_cmd == NULL)
			ft_free_malloc(shell);
	}
	ft_create_lst(shell);
	if (ft_parsing_bis(shell, envp) == -1)
		return ;
	ft_print_test(shell); //A SUPPR
	ft_free(shell, NULL);
}

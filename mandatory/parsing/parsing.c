/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:01:37 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/23 14:59:57 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_len_without_quote(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] != '\"')
			size++;
		i++;
	}
	return (size);
}

char	*ft_delete_quotes(char *str, t_shell *shell, t_cmds *cmds)
{
	int		i;
	char	*new_str;
	int		size;
	int		size_copy;

	size = ft_len_without_quote(str);
	new_str = ft_calloc(sizeof(char *), (size + 1));
	if (!new_str)
		ft_free_error(shell, cmds, "Malloc");
	i = 0;
	size_copy = 0;
	while (str[i])
	{
		if (str[i] != '\"')
		{
			new_str[size_copy] = str[i];
			size_copy++;
		}
		i++;
	}
	free(str);
	new_str[size_copy] = '\0';
	return (new_str);
}

int	ft_verif_quote(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			quote++;
		i++;
	}
	if (quote % 2 != 0)
		return (1);
	return (quote);
}

int	ft_verif_pipe(char *s, t_shell *shell, t_cmds *cmds)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	if (s[i] == '|')
	{
		ft_putendl_fd("Wrong quotes syntax", 2);
		return (-1);
	}
	while (s[i])
	{
		if (s[i] == '|')
			pipe++;
		if (s[i + 1] == '\0' && s[i] == '|')
		{
			ft_putendl_fd("Wrong quotes syntax", 2);
			return (-1);
		}
		//A mettre dans une autre fonction apres le split ?
		/* if (s[i] == '|' && s[i + 1] == '|') */
		/* { */
		/* 	ft_putendl_fd("Wrong quotes syntax", 2); */
		/* 	return (-1); */
		/* } */
		i++;
	}
	return (pipe);
}

void	ft_create_linked_lst(t_cmds **cmds, t_shell *shell)
{
	int		j;
	t_cmds	*new;

	j = 1;
	*cmds = ft_lstnew_cmd(shell->tab_cmd[0]);
	while (shell->tab_cmd[j] != NULL)
	{
		new = ft_lstnew_cmd(shell->tab_cmd[j]);
		ft_lstaddback_cmd(cmds, new);
		j++;
	}
}

void	ft_parsing(char *str, t_shell *shell, t_cmds *cmds, char **envp)
{
	(void) envp;
	if (ft_verif_quote(str) == 1)
	{
		ft_putendl_fd("Wrong quotes syntax", 2);
		return ;
	}
	if (ft_verif_pipe(str, shell, cmds) == -1)
		return ;
	else
	{
		shell->tab_cmd = ft_split_shell(str);
		if (shell->tab_cmd == NULL)
			ft_free_error(shell, cmds, "Malloc");
	}
	ft_verif_pipe(str, shell, cmds);
	ft_create_linked_lst(&cmds, shell);
	ft_print_test(shell, cmds); //A SUPPR
	ft_free_tab_char(shell->tab_cmd);
}

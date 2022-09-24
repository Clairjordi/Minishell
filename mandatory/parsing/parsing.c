/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:01:37 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/24 16:39:57 by clorcery         ###   ########.fr       */
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
		ft_free_malloc(shell, cmds);
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

int	ft_count_quote(char *str)
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
	{
		ft_putendl_fd("Wrong quotes syntax", 2);
		return (-1);
	}
	return (quote);
}

int	ft_verif_pipe(char *s)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	if (s[i] == '|')
	{
		ft_putendl_fd("Wrong pipes syntax", 2);
		return (-1);
	}
	while (s[i])
	{
		if (s[i] == '|')
			pipe++;
		if (s[i + 1] == '\0' && s[i] == '|')
		{
			ft_putendl_fd("Wrong pipes syntax", 2);
			return (-1);
		}
		i++;
	}
	return (pipe);
}

void	ft_create_linked_lst(t_cmds **cmds, t_shell *shell)
{
	int		j;
	t_cmds	*new;

	j = 1;
	shell->fill_lst = 1;
	*cmds = ft_lstnew_cmd(shell->tab_cmd[0]);
	while (shell->tab_cmd[j] != NULL)
	{
		new = ft_lstnew_cmd(shell->tab_cmd[j]);
		ft_lstaddback_cmd(cmds, new);
		j++;
	}
	//EN ATTENTE - creer un seul element entre les pipes
	/* while (shell->tab_cmd[j] != NULL) */
	/* { */
	/* 	if (ft_strcmp(shell->tab_cmd[j], "|") == 0 || shell->tab_cmd[j + 1] == NULL) */
	/* 	{ */
	/* 		new = ft_lstnew_cmd(shell->tab_cmd[j]); */
	/* 		ft_lstaddback_cmd(cmds, new); */
	/* 	} */
	/* 	j++; */
	/* } */
}


int	ft_check_pipe(t_shell *shell, t_cmds *cmds)
{
	int	i;
	int	j;

	i = 0;
	while (shell->tab_cmd[i] != NULL)
	{
		j = 0;
		while (shell->tab_cmd[i][j])
		{
			if (shell->tab_cmd[i][j] == '|' && shell->tab_cmd[i][j + 1] == '|')
			{
				ft_free(shell, cmds, "Wrong pipes syntax");
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_verif_parsing(t_shell *shell, t_cmds *cmds)
{
	if (ft_check_pipe(shell, cmds) == -1)
		return (-1);
	return (0);
}

void	ft_parsing(char *str, t_shell *shell, t_cmds *cmds, char **envp)
{
	(void) envp;
	if (ft_count_quote(str) == -1)
		return ;
	if (ft_verif_pipe(str) == -1)
		return ;
	else
	{
		shell->tab_cmd = ft_split_shell(str);
		if (shell->tab_cmd == NULL)
			ft_free_malloc(shell, cmds);
	}
	if (ft_verif_parsing(shell, cmds) == -1) //free fait dans les fonctions
		return ;
	ft_create_linked_lst(&cmds, shell);
	ft_print_test(shell, cmds); //A SUPPR
	ft_free(shell, cmds, NULL);
	shell->fill_lst = 0;
}

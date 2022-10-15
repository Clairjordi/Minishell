/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:31:44 by mcloarec          #+#    #+#             */
/*   Updated: 2022/10/15 19:13:57 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_path_cmd(char *path_cmd)
{
	if (access(path_cmd, F_OK | X_OK))
		return (0);
	else
		return (-1);
}

int	get_path(t_shell *shell, char *path_cmd, char **envp)
{
	char	*path;
	int		i;
	char	*path_test;

	find_path(shell, envp);
	if (access(path_cmd, X_OK) == 0)
	{
		shell->arg->cmd_path = ft_strdup(path_cmd);
		return (0);
	}
	i = -1;
	path = NULL;
	path_test = NULL;
	while (shell->path[++i])
	{
		path = ft_strjoin(shell->path[i], "/");
		path_test = ft_strjoin(path, path_cmd);
		free(path);
		if (check_path_cmd(path_test))
		{
			shell->arg->cmd_path = ft_strdup(path_test);
			free(path_test);
			return (0);
		}
		free(path_test);
	}
	/* if (shell->path[i] == NULL) */
	/* 	return (-1); */
	/* if (check_path_cmd(shell->arg->cmd_path) == -1) */
	/* { */
	/* 	ft_free(shell, "command not found"); */
	/* 	return (-1); */
	/* } */
	return (-1);
}

void	find_path(t_shell *shell, char **envp)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (envp[i++])
	{
		path = ft_strnstr(envp[i], "PATH", 5);
		if (path)
			break ;
	}
	shell->path = ft_split(path + 5, ':');
}

int	ft_if_redirect(t_shell *shell, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '<')
			shell->arg->redir_l = 1;
		else if (s[i] == '>')
			shell->arg->redir_r = 1;
		else if (s[i] == '<' && s[i + 1] == '<')
			shell->arg->heredoc = 1;
		else if (s[i] == '>' && s[i + 1] == '>')
			shell->arg->append = 1;
		else
			return (-1);
		i++;
	}
	return (0);
}

int	ft_sort_value(t_shell *shell, char **envp)
{
	t_cmds	*lst;
	int		i;

	i = 0;
	lst = shell->arg;
	while (lst)
	{
		if (i == 0)
		{	
			if (get_path(shell, lst->value_split[i], envp) == -1
				&& ft_if_redirect(shell, lst->value_split[i]) == -1)
				ft_printf("First arg must be a cmd or a redirection\n");
			else
				ft_printf("cool\n");
		}
		ft_sort_value_bis(shell, envp);
		lst = lst->next;
	}
	return (0);
}

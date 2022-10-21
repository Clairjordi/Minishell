/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:57:08 by clorcery          #+#    #+#             */
/*   Updated: 2022/10/21 19:03:32 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_path_cmd(char *path_cmd)
{
	if (access(path_cmd, F_OK | X_OK))
		return (0);
	else
		return (-1);
}

void	ft_find_path(t_shell *shell, char **envp)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (envp[i])
	{
		path = ft_strnstr(envp[i], "PATH", 5);
		if (path)
			break ;
		i++;
	}
	shell->path = ft_split(path + 5, ':');
}

int	ft_get_path(t_shell *shell, char *path_cmd, char **envp)
{
	char	*path;
	int		i;

	find_path(shell, envp);
	if (access(path_cmd, X_OK) == 0)
	{
		shell->exec->cmd_path = ft_strdup(path_cmd);
		return (0);
	}
	i = 0;
	path = NULL;
	while (shell->path[i])
	{
		path = ft_strjoin(shell->path[i], "/");
		shell->exec->cmd_path = ft_strjoin(path, path_cmd);
		free(path);
		if (check_path_cmd(shell->exec->cmd_path))
			return (0);
		free(shell->exec->cmd_path);
		i++;
	}
	shell->exec->cmd_path = NULL;
	return (-1);
}

/* int	get_path(t_shell *shell, char *path_cmd, char **envp) */
/* { */
/* 	char	*path; */
/* 	int		i; */
/* 	char	*path_test; */
/*  */
/* 	find_path(shell, envp); */
/* 	if (access(path_cmd, X_OK) == 0) */
/* 	{ */
/* 		shell->exec->cmd_path = ft_strdup(path_cmd); */
/* 		return (0); */
/* 	} */
/* 	i = 0; */
/* 	path = NULL; */
/* 	path_test = NULL; */
/* 	while (shell->path[i]) */
/* 	{ */
/* 		path = ft_strjoin(shell->path[i], "/"); */
/* 		path_test = ft_strjoin(path, path_cmd); */
/* 		free(path); */
/* 		if (check_path_cmd(path_test)) */
/* 		{ */
/* 			shell->exec->cmd_path = ft_strdup(path_test); */
/* 			free(path_test); */
/* 			return (0); */
/* 		} */
/* 		free(path_test); */
/* 		i++; */
/* 	} */
/* 	return (-1); */
/* } */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:57:08 by clorcery          #+#    #+#             */
/*   Updated: 2022/10/17 18:06:36 by clorcery         ###   ########.fr       */
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

int	get_path(t_shell *shell, char *path_cmd, char **envp)
{
	char	*path;
	int		i;

	find_path(shell, envp);
	if (access(path_cmd, X_OK) == 0)
	{
		shell->arg->cmd_path = ft_strdup(path_cmd);
		return (0);
	}
	i = 0;
	path = NULL;
	while (shell->path[i])
	{
		path = ft_strjoin(shell->path[i], "/");
		shell->arg->cmd_path = ft_strjoin(path, path_cmd);
		free(path);
		if (check_path_cmd(shell->arg->cmd_path))
			return (0);
		free(shell->arg->cmd_path);
		i++;
	}
	shell->arg->cmd_path = NULL;
	return (-1);
}

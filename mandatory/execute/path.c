/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:57:08 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/03 13:27:13 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_get_path_bis(t_shell *shell, char *path_test)
{
	if (shell->exec->cmd_path == NULL)
	{
		shell->exec->cmd_path = ft_strdup(path_test);
		if (!shell->exec->cmd_path)
			ft_free_malloc(shell);
	}
	else
	{
		free(shell->exec->cmd_path);
		shell->exec->cmd_path = ft_strdup(path_test);
		if (!shell->exec->cmd_path)
			ft_free_malloc(shell);
	}
}

char	*ft_check_path(t_shell *shell, char *path_test, char *path_cmd, int i)
{
	char	*path;

	path = NULL;
	path = ft_strjoin(shell->path[i], "/");
	if (path == NULL)
		ft_free_malloc(shell);
	path_test = ft_strjoin_free(path, path_cmd, 1);
	if (path_test == NULL)
	{
		free(path);
		ft_free_malloc(shell);
	}
	return (path_test);
}

char	*ft_get_path(t_shell *shell, char *path_cmd, char **envp)
{
	int		i;
	char	*path_test;

	if (shell->path == NULL)
		ft_find_path(shell, envp);
	if (ft_check_access(shell, path_cmd) == TRUE)
		return (shell->exec->cmd_path);
	i = 0;
	path_test = NULL;
	while (shell->path[i])
	{
		path_test = ft_check_path(shell, path_test, path_cmd, i);
		if (ft_check_path_cmd(path_test) == 0)
		{
			ft_get_path_bis(shell, path_test);
			free(path_test);
			return (shell->exec->cmd_path);
		}
		free(path_test);
		i++;
	}
	return (NULL);
}

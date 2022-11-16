/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:57:08 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/16 17:09:23 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_get_path_bis(t_shell *shell, char *path_tmp)
{
	if (shell->exec->cmd_path == NULL)
	{
		shell->exec->cmd_path = ft_strdup(path_tmp);
		if (!shell->exec->cmd_path)
			ft_free_malloc(shell);
	}
	else
	{
		free(shell->exec->cmd_path);
		shell->exec->cmd_path = ft_strdup(path_tmp);
		if (!shell->exec->cmd_path)
			ft_free_malloc(shell);
	}
}

char	*ft_check_path(t_shell *shell, char *path_tmp, char *cmd, int i)
{
	char	*path;

	path = NULL;
	path = ft_strjoin(shell->path[i], "/");
	if (path == NULL)
		ft_free_malloc(shell);
	path_tmp = ft_strjoin_free(path, cmd, 1);
	if (path_tmp == NULL)
	{
		free(path);
		ft_free_malloc(shell);
	}
	return (path_tmp);
}

char	*ft_get_path(t_shell *shell, char *cmd)
{
	int		i;
	char	*path_tmp;

	if (shell->path == NULL)
	{
		if (ft_find_path(shell) == NULL)
			return (NULL);
	}
	if (ft_check_access(shell, cmd) == TRUE)
		return (shell->exec->cmd_path);
	i = 0;
	path_tmp = NULL;
	while (shell->path[i])
	{
		path_tmp = ft_check_path(shell, path_tmp, cmd, i);
		if (ft_check_path_cmd(path_tmp) == 0)
		{
			ft_get_path_bis(shell, path_tmp);
			free(path_tmp);
			return (shell->exec->cmd_path);
		}
		free(path_tmp);
		i++;
	}
	return (NULL);
}

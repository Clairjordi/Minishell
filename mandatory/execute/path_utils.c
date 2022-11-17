/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:32:15 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/17 09:38:04 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_access(t_shell *shell, char *path_cmd)
{
	if (access(path_cmd, X_OK) == 0)
	{
		if (shell->exec->cmd_path == NULL)
		{
			shell->exec->cmd_path = ft_strdup(path_cmd);
			if (shell->exec->cmd_path == NULL)
				ft_free_malloc(shell);
		}
		else
		{
			free(shell->exec->cmd_path);
			shell->exec->cmd_path = ft_strdup(path_cmd);
			if (shell->exec->cmd_path == NULL)
				ft_free_malloc(shell);
		}
		return (TRUE);
	}
	return (FALSE);
}

int	ft_check_path_cmd(char *path_cmd)
{
	if (access(path_cmd, F_OK | X_OK) == 0)
		return (0);
	else
		return (-1);
}

char	*ft_find_path(t_shell *shell)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (shell->built->env[i])
	{
		path = ft_strnstr(shell->built->env[i], "PATH", 5);
		if (path)
			break ;
		i++;
	}
	if (shell->built->env[i] == NULL)
	{
		path = NULL;
		return (path);
	}
	shell->path = ft_split(path + 5, ':');
	if (shell->path == NULL)
		ft_free_malloc(shell);
	return (path);
}

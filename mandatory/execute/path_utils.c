/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:32:15 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/03 13:27:24 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_access(t_shell *shell, char *path_cmd)
{
	if (access(path_cmd, X_OK) == 0)
	{
		if (shell->exec->cmd_path == NULL)
			shell->exec->cmd_path = ft_strdup(path_cmd);
		else
		{
			free(shell->exec->cmd_path);
			shell->exec->cmd_path = ft_strdup(path_cmd);
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

void	ft_find_path(t_shell *shell, char **envp)
{
	char	*path;
	int		i;

	//(void) envp;
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
	if (shell->path == NULL)
		ft_free_malloc(shell);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:32:37 by mcloarec          #+#    #+#             */
/*   Updated: 2022/10/28 18:46:33 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_shell_pipe(t_shell *shell, t_cmds *lst)
{
	if (shell->pipe > 1)
	{
		if (pipe(lst->pipe_fd) == ERROR)
		{
			perror("ERROR pipe");
			return (ERROR);
		}
		shell->pipe--;
	}
	return (shell->pipe);
}

void	ft_waitpid_pipe(t_shell *shell)
{
	int	i;
	int	wstatus;

	i = 0;
	wstatus = 0;
	while (shell->tab_pid[i])
	{
		if (waitpid(ft_atoi(shell->tab_pid[i]), &wstatus, 0) == ERROR)
			perror("ERROR waitpid");
		i++;
	}
	ft_status_child(wstatus);
}

void	ft_add_pid(t_shell *shell)
{
	if (shell->tab_pid == NULL)
	{
		shell->tab_pid = ft_calloc(sizeof(char *), 2);
		shell->tab_pid[0] = ft_itoa(shell->exec->pid);
		shell->tab_pid[1] = NULL;
	}
	else
		shell->tab_pid = ft_realloc_tab_char(shell->tab_pid,
				ft_itoa(shell->exec->pid));
}

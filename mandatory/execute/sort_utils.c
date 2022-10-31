/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:32:37 by mcloarec          #+#    #+#             */
/*   Updated: 2022/10/31 18:02:42 by clorcery         ###   ########.fr       */
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
	if (shell->tab_pid == NULL)
		return ;
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
	if (shell->tab_pid == NULL && shell->exec->pid != 0)
	{
		shell->tab_pid = ft_calloc(sizeof(char *), 2);
		if (shell->tab_pid == NULL)
			ft_free_malloc(shell);
		shell->tab_pid[0] = ft_itoa(shell->exec->pid);
		if (shell->tab_pid[0] == NULL)
			ft_free_malloc(shell);
		shell->tab_pid[1] = NULL;
	}
	else if(shell->exec->pid != 0)
	{
		shell->tmp = ft_itoa(shell->exec->pid);
		if (shell->tmp == NULL)
			ft_free_malloc(shell);
		shell->tab_pid = ft_realloc_tab_char(shell->tab_pid, shell->tmp);
		if (shell->tab_pid == NULL)
			ft_free_malloc(shell);
	}
	shell->exec->pid = 0;
	free(shell->tmp);
	shell->tmp = NULL;
}

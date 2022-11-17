/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:32:37 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/17 10:52:04 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_shell_pipe(t_shell *shell, t_cmds *lst)
{
	if (shell->pipe > 1)
	{
		if (pipe(lst->pipe_fd) == ERROR)
		{
			perror("ERROR pipe ");
			return (ERROR);
		}
		shell->pipe--;
	}
	return (shell->pipe);
}

int	ft_check_last(t_shell *shell)
{
	t_cmds	*lst;

	lst = shell->arg;
	while (lst->next != NULL)
	lst = lst->next;
	if (lst->hdoc == TRUE)
		return (1);
	else if (lst->cmd_found == FALSE)
		return (2);
	else
		return (0);
}

void	ft_waitpid_pipe(t_shell *shell, int wstatus)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = g_minishell.status;
	if (shell->tab_pid == NULL)
	{	
		if (ft_check_last(shell) == 1)
			g_minishell.status = 0;
		return ;
	}
	while (shell->tab_pid[i])
	{
		if (waitpid(ft_atoi(shell->tab_pid[i]), &wstatus, 0) == ERROR)
			perror("ERROR waitpid ");
		i++;
	}
	ft_status_child(wstatus);
	if (ft_check_last(shell) == 1)
		g_minishell.status = 0;
	else if ((ft_size_lst(shell->arg) != i && ft_check_last(shell) == 2)
		|| (ft_size_lst(shell->arg) != i && tmp == 1)
		|| g_minishell.status == 141 || tmp == 127)
		g_minishell.status = tmp;
	g_minishell.is_in_loop = 0;
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
	else if (shell->exec->pid != 0)
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

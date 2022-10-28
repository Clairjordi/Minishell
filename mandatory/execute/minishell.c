/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:35:26 by mcloarec          #+#    #+#             */
/*   Updated: 2022/10/28 12:01:45 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execute_cmd(t_shell *shell, t_exec *exec, char **envp, t_cmds *lst)
{
	if (lst->hdoc == TRUE)
	{
		exec->infile = open(".heredoc", O_RDONLY, 0644);
		if (exec->infile == ERROR)
			perror("ERROR infile");
	}
	exec->pid = fork();
	if (exec->pid == ERROR)
		perror("ERROR pid");
	 if (exec->pid == 0)
		ft_child_cmd(shell, exec, envp);
	else
	{
		if (waitpid(exec->pid, NULL, 0) == ERROR)
			perror("ERROR waitpid");
	}
}

void	ft_execute_pipe(t_shell *shell, t_exec *exec, char **envp, t_cmds *lst)
{
	if (lst->hdoc == TRUE)
	{
		exec->infile = open(".heredoc", O_RDONLY, 0644);
		if (exec->infile == ERROR)
			perror("ERROR infile");
	}
	exec->pid = fork();
	if (exec->pid == ERROR)
		perror("ERROR pid");
	if (exec->pid == 0)
		ft_check_child_execute(shell, envp, lst);
	else
	{
		if (waitpid(exec->pid, NULL, 0) == ERROR)
			perror("ERROR waitpid");
	}
	if (lst->prev != NULL && lst->next != NULL)
		close(lst->prev->pipe_fd[0]);
	if (lst->next != NULL)
		close(lst->pipe_fd[1]);
}

void	ft_minishell(t_shell *shell, char **envp)
{
	if (ft_check_error_redirect(shell) == FALSE)
		return ;
	ft_count_heredoc(shell);
	if (shell->arg->hdoc == TRUE)
		ft_init_heredoc(shell);
	ft_check_execute(shell, envp);
}

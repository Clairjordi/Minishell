/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:35:26 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/05 13:07:00 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_execute_builtins_bis(t_shell *shell, int wstatus, t_cmds *lst)
{
	pid_t pid;

	pid = fork();
	if (pid == ERROR)
		perror("ERROR pid");
	if (pid == 0)
		ft_child_builtins_bis(shell, shell->exec, lst);
	else
	{
		if (waitpid(pid, &wstatus, 0) == ERROR)
			perror("ERROR waitpid");
		close(lst->pipe_fd[0]);
		close(lst->pipe_fd[1]);
	}
	return (wstatus);
}

int	ft_execute_builtins(t_shell *shell, int wstatus, t_cmds *lst)
{
	pid_t pid_builtins;

	pid_builtins = fork();
	if (pid_builtins == ERROR)
		perror("ERROR pid");
	if (pid_builtins == 0)
		ft_child_builtins(shell, shell->exec, lst);
	else
	{
		if (waitpid(pid_builtins, &wstatus, 0) == ERROR)
			perror("ERROR waitpid");
		close(lst->pipe_fd[1]);
	}
	wstatus = ft_execute_builtins_bis(shell, wstatus, lst);
	return (wstatus);
}

int	ft_execute_cmd(t_shell *shell, char **envp, int wstatus)
{
	shell->exec->pid = fork();
	if (shell->exec->pid == ERROR)
		perror("ERROR pid");
	if (shell->exec->pid == 0)
	{
		g_g.is_in_loop = 3;
		signal(SIGQUIT, SIG_DFL);
		ft_child_cmd(shell, shell->exec, envp);
	}
	g_g.is_in_loop = 2;
	if (waitpid(shell->exec->pid, &wstatus, 0) == ERROR)
		perror("ERROR waitpid");
	g_g.is_in_loop = 0;
	return (wstatus);
}

void	ft_execute_pipe(t_shell *shell, t_exec *exec, char **envp, t_cmds *lst)
{
	exec->pid = fork();
	if (exec->pid == ERROR)
		perror("ERROR pid");
	if (exec->pid == 0)
	{
		g_g.is_in_loop = 3;
		signal(SIGQUIT, SIG_DFL);
		if (lst->prev != NULL && lst->prev->pipe_fd[1] > 2)
			close(lst->prev->pipe_fd[1]);
		if (lst->pipe_fd[0] > 2)
			close(lst->pipe_fd[0]);
		ft_check_child_execute(shell, envp, lst);
	}
	g_g.is_in_loop = 2;
	if (lst->next != NULL)
	{
		close(lst->pipe_fd[1]);
		lst->pipe_fd[1] = 0;
	}
}

void	ft_minishell(t_shell *shell, char **envp)
{
	if (ft_check_error_redirect(shell) == FALSE)
		return ;
	ft_count_heredoc(shell);
	if (ft_init_heredoc(shell) == ERROR)
		return ;
	ft_check_execute(shell, envp);
}

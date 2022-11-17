/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:40:40 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/17 09:34:04 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_child_cmd(t_shell *shell, t_exec *exec)
{
	if (exec->infile > 2)
	{
		if (dup2(exec->infile, STDIN_FILENO) == ERROR)
			perror("ERROR dup ");
	}
	if (exec->outfile > 2)
	{
		if (dup2(exec->outfile, STDOUT_FILENO) == ERROR)
			perror("ERROR dup ");
	}
	if (shell->exec->builtins != NULL)
	{
		ft_exec_builtins(shell);
		ft_close_std();
		ft_free_child(shell);
		exit(g_minishell.status);
	}
	else if (execve(exec->cmd_path, exec->cmd, shell->built->env) == ERROR)
	{
		ft_free(shell, "ERROR execve ");
		g_minishell.status = 127;
		exit(g_minishell.status);
	}
	g_minishell.status = 0;
	exit(g_minishell.status);
}

void	ft_first_child(t_exec *exec, t_cmds *lst)
{
	if (exec->infile > 2)
	{
		if (dup2(exec->infile, STDIN_FILENO) == ERROR)
			perror("ERROR dup ");
	}
	if (exec->cmd != NULL)
		close (lst->pipe_fd[0]);
	if (exec->outfile > 2)
	{
		if (dup2(exec->outfile, lst->pipe_fd[1]) == ERROR)
			perror("ERROR dup ");
	}
	if (dup2(lst->pipe_fd[1], STDOUT_FILENO) == ERROR)
		perror("ERROR dup ");
	close(lst->pipe_fd[1]);
}

void	ft_last_child(t_exec *exec, t_cmds *lst)
{
	if (exec->infile > 2)
	{
		if (dup2(exec->infile, lst->prev->pipe_fd[0]) == ERROR)
			perror("ERROR dup ");
	}
	if (dup2(lst->prev->pipe_fd[0], STDIN_FILENO) == ERROR)
		perror("ERROR dup ");
	close(lst->prev->pipe_fd[0]);
	if (exec->outfile > 2)
	{
		if (dup2(exec->outfile, STDOUT_FILENO) == ERROR)
			perror("ERROR dup ");
	}
}

void	ft_else_child(t_exec *exec, t_cmds *lst)
{
	if (exec->infile > 2)
	{
		if (dup2(exec->infile, lst->prev->pipe_fd[0]) == ERROR)
			perror("ERROR dup ");
	}
	if (dup2(lst->prev->pipe_fd[0], STDIN_FILENO) == ERROR)
		perror("ERROR dup ");
	if (exec->cmd != NULL)
		close (lst->pipe_fd[0]);
	close(lst->prev->pipe_fd[0]);
	if (exec->outfile > 2)
	{
		if (dup2(exec->outfile, lst->pipe_fd[1]) == ERROR)
			perror("ERROR dup ");
	}
	if (dup2(lst->pipe_fd[1], STDOUT_FILENO) == ERROR)
		perror("ERROR dup ");
	close(lst->pipe_fd[1]);
}

void	ft_check_child_execute(t_shell *shell, t_cmds *lst)
{
	t_exec	*exec;

	exec = shell->exec;
	if (lst->prev == NULL)
		ft_first_child(exec, lst);
	else if (lst->next == NULL)
		ft_last_child(exec, lst);
	else
		ft_else_child(exec, lst);
	if (shell->exec->builtins != NULL)
	{
		ft_exec_builtins(shell);
		close(lst->pipe_fd[0]);
		ft_close_std();
		ft_free_child(shell);
		exit(g_minishell.status);
	}
	if (execve(exec->cmd_path, exec->cmd, shell->built->env) == ERROR)
	{	
		ft_free(shell, "ERROR execve ");
		g_minishell.status = 127;
		exit(g_minishell.status);
	}
	g_minishell.status = 0;
	exit(g_minishell.status);
}

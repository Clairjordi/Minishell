/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:40:40 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/04 10:19:48 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

void	ft_child_cmd(t_shell *shell, t_exec *exec, char **envp)
{
	if (dup2(exec->infile, STDIN_FILENO) == ERROR)
		perror("ERROR dup");
	if (exec->outfile > 2)
	{
		if (dup2(exec->outfile, STDOUT_FILENO) == ERROR)
			perror("ERROR dup");
	}
	if (execve(exec->cmd_path, exec->cmd, envp) == ERROR)
	{
		close (exec->infile);
		ft_free(shell, "ERROR execve");
		g_g.status = 127;
		exit(1);
	}
	g_g.status = 0;
}

void	ft_first_child(t_exec *exec, t_cmds *lst)
{	
	if (exec->infile > 2)
	{
		if (dup2(exec->infile, STDIN_FILENO) == ERROR)
			perror("ERROR dup 1");
	}
	if (dup2(STDIN_FILENO, lst->pipe_fd[0]) == ERROR)
		perror("ERROR dup 2");
	if (exec->outfile > 2)
	{
		if (dup2(exec->outfile, lst->pipe_fd[1]) == ERROR)
			perror("ERROR dup 3");
	}
	if (dup2(lst->pipe_fd[1], STDOUT_FILENO) == ERROR)
		perror("ERROR dup 4");
}

void	ft_last_child(t_exec *exec, t_cmds *lst)
{
	if (exec->infile > 2)
	{
		if (dup2(exec->infile, lst->prev->pipe_fd[0]) == ERROR)
			perror("ERROR dup 5");
	}
	if (dup2(lst->prev->pipe_fd[0], STDIN_FILENO) == ERROR)
		perror("ERROR dup 6");
	if (exec->outfile > 2)
	{
		if (dup2(exec->outfile, STDOUT_FILENO) == ERROR)
			perror("ERROR dup 7");
	}
}

void	ft_else_child(t_exec *exec, t_cmds *lst)
{
	if (exec->infile > 2)
	{
		if (dup2(exec->infile, lst->prev->pipe_fd[0]) == ERROR)
			perror("ERROR dup 8");
	}
	if (dup2(lst->prev->pipe_fd[0], STDIN_FILENO) == ERROR)
		perror("ERROR dup 9");
	if (exec->outfile > 2)
	{
		if (dup2(exec->outfile, lst->pipe_fd[1]) == ERROR)
			perror("ERROR dup 10");
	}
	if (dup2(lst->pipe_fd[1], STDOUT_FILENO) == ERROR)
		perror("ERROR dup 11");
}

void	ft_check_child_execute(t_shell *shell, char **envp, t_cmds *lst)
{
	t_exec	*exec;

	exec = shell->exec;
	if (lst->prev == NULL)
		ft_first_child(exec, lst);
	else if (lst->next == NULL)
		ft_last_child(exec, lst);
	else
		ft_else_child(exec, lst);
	if (execve(exec->cmd_path, exec->cmd, envp) == ERROR)
	{	
		close (exec->infile);
		ft_free(shell, "ERROR execve");
		g_g.status = 127;
		exit(1);
	}
	g_g.status = 0;
}

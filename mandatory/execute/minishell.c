/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:35:26 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/01 12:18:00 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_execute_cmd(t_shell *shell, char **envp, t_cmds *lst, int wstatus)
{
	(void) *lst;
	shell->exec->pid = fork();
	if (shell->exec->pid == ERROR)
		perror("ERROR pid");
	if (shell->exec->pid == 0)
	{
		
		g_g.is_in_heredoc = 3;
		signal(SIGQUIT, SIG_DFL);
		ft_child_cmd(shell, shell->exec, envp);
	}
	g_g.is_in_heredoc = 2;
	if (waitpid(shell->exec->pid, &wstatus, 0) == ERROR)
		perror("ERROR waitpid");
	g_g.is_in_heredoc = 0;
	return (wstatus);
}

int	ft_verif_cat_bis(t_shell *shell, t_cmds *lst)
{
	if (ft_strcmp(lst->value_split[0], "cat") == 0)
	{
		if (shell->exec->infile == 0 && shell->exec->outfile == 0)
			return (FALSE);
	}
	return (TRUE);
}

void	ft_execute_pipe(t_shell *shell, t_exec *exec, char **envp, t_cmds *lst)
{
	(void) *lst;
	exec->pid = fork();
	if (exec->pid == ERROR)
		perror("ERROR pid");
	if (exec->pid == 0)
	{
		g_g.is_in_heredoc = 3;
		signal(SIGQUIT, SIG_DFL);
		ft_check_child_execute(shell, envp, lst);
	}
	g_g.is_in_heredoc = 2;
	if (lst->prev != NULL && lst->next != NULL && lst->hdoc == FALSE
			&& ft_verif_cat_bis(shell, lst) == TRUE)
	{
		close(lst->prev->pipe_fd[0]);
		lst->prev->pipe_fd[0] = 0;
	}
	if (lst->next != NULL)
		close(lst->pipe_fd[1]);
}

void	ft_minishell(t_shell *shell, char **envp)
{
	if (ft_check_error_redirect(shell) == FALSE)
		return ;
	ft_count_heredoc(shell);
	if (ft_init_heredoc(shell) == ERROR)
		return ;
	if (ft_check_execute(shell, envp) == ERROR)
		return ;
}

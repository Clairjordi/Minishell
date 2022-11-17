/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:25:29 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/17 16:25:56 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_heredoc(t_shell *shell)
{
	ft_free(shell, NULL);
	ft_free_envcpy(shell);
	while (1)
	{
		g_minishell.line = readline (">");
		if (!g_minishell.line)
		{
			ft_putstr_fd("heredoc delimited by end-of-file\n", 1);
			g_minishell.status = 0;
			break ;
		}
		if (ft_strcmp(g_minishell.line, g_minishell.limiter) == 0)
			break ;
		else
		{
			ft_putstr_fd(g_minishell.line, g_minishell.fd_hdoc);
			ft_putstr_fd("\n", g_minishell.fd_hdoc);
			free(g_minishell.line);
			g_minishell.line = NULL;
		}
	}
	free(g_minishell.line);
	free(g_minishell.limiter);
	close(g_minishell.fd_hdoc);
	exit(EXIT_SUCCESS);
}

int	ft_fork_heredoc(t_shell *shell, int wstatus, t_cmds *lst)
{
	ft_get_idx_heredoc(lst);
	g_minishell.fd_hdoc = open(".heredoc", (O_CREAT | O_WRONLY | O_TRUNC),
			0644);
	g_minishell.limiter = ft_strdup(lst->value_split[lst->idx_hdoc]);
	if (g_minishell.limiter == NULL)
		ft_free_malloc(shell);
	shell->pid_hdoc = fork();
	if (shell->pid_hdoc == -1)
	{
		ft_putendl_fd("Fork doesn't work", 2);
		g_minishell.status = 1;
		ft_free_malloc(shell);
	}
	else if (shell->pid_hdoc == 0)
	{
		g_minishell.is_in_loop = 1;
		ft_heredoc(shell);
	}
	g_minishell.is_in_loop = 2;
	free(g_minishell.limiter);
	close(g_minishell.fd_hdoc);
	if (waitpid(shell->pid_hdoc, &wstatus, 0) == ERROR)
		perror("ERROR waitpid heredoc ");
	g_minishell.is_in_loop = 0;
	return (wstatus);
}

int	ft_init_heredoc(t_shell *shell)
{	
	t_cmds	*lst;
	int		wstatus;

	lst = shell->arg;
	wstatus = 0;
	while (lst)
	{
		if (lst->hdoc == TRUE)
		{
			while (lst->count_hdoc > 0)
			{
				wstatus = ft_fork_heredoc(shell, wstatus, lst);
				ft_status_child(wstatus);
				if (wstatus != 0)
					return (ERROR);
				lst->count_hdoc--;
			}
		}
		lst = lst->next;
	}
	return (0);
}

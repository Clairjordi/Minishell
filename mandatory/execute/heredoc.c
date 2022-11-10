/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:25:29 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/10 11:41:17 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_heredoc(t_shell *shell)
{
	ft_free(shell, NULL);
	while (1)
	{
		g_g.line = readline (">");
		if (!g_g.line)
		{
			ft_putstr_fd("bash: warning: here-document \
					at g_g.line 1 delimited by end-of-file\n", 1);
			g_g.status = 0;
			break ;
		}
		if (ft_strcmp(g_g.line, g_g.limiter) == 0)
			break ;
		else
		{
			ft_putstr_fd(g_g.line, g_g.fd_hdoc);
			ft_putstr_fd("\n", g_g.fd_hdoc);
			free(g_g.line);
			g_g.line = NULL;
		}
	}
	free(g_g.line);
	free(g_g.limiter);
	close(g_g.fd_hdoc);
	exit(EXIT_SUCCESS);
}

int	ft_fork_heredoc(t_shell *shell, int wstatus, t_cmds *lst)
{
	ft_get_idx_heredoc(lst);
	g_g.fd_hdoc = open(".heredoc", (O_CREAT | O_WRONLY | O_TRUNC), 0644);
	g_g.limiter = ft_strdup(lst->value_split[lst->idx_hdoc]);
	if (g_g.limiter == NULL)
		ft_free_malloc(shell);
	shell->pid_hdoc = fork();
	if (shell->pid_hdoc == -1)
	{
		ft_putendl_fd("Fork doesn't work", 2);
		g_g.status = 1;
		ft_free_malloc(shell);
	}
	else if (shell->pid_hdoc == 0)
	{
		g_g.is_in_loop = 1;
		ft_heredoc(shell);
	}
	g_g.is_in_loop = 2;
	free(g_g.limiter);
	close(g_g.fd_hdoc);
	if (waitpid(shell->pid_hdoc, &wstatus, 0) == ERROR)
		perror("ERROR waitpid heredoc");
	g_g.is_in_loop = 0;
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

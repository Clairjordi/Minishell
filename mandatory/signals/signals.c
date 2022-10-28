/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:45:27 by clorcery          #+#    #+#             */
/*   Updated: 2022/10/28 17:14:05 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT && g_g.is_in_heredoc == 1)
	{
		free(g_g.line);
		free(g_g.limiter);
		close(g_g.fd_hdoc);
		exit (130);
	}
	else if (sig == SIGINT && g_g.is_in_heredoc == 0)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_status_child(int wstatus)
{
	if (WIFEXITED(wstatus))
	{
		g_g.status = WEXITSTATUS(wstatus);
	}
	if (WIFSIGNALED(wstatus))
	{
		g_g.status = WTERMSIG(wstatus);
		if (g_g.status != 131)
			g_g.status += 128;
	}
	if (g_g.status == 131)
		ft_putstr_fd("Quit (core dumped)\n", 2);
}

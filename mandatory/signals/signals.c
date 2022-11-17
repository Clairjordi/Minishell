/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:45:27 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/16 18:56:47 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT && g_minishell.is_in_loop == 1)
	{
		free(g_minishell.line);
		free(g_minishell.limiter);
		close(g_minishell.fd_hdoc);
		exit(130);
	}
	else if (sig == SIGINT && g_minishell.is_in_loop == 0)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_minishell.status = 130;
	}
	else if (sig == SIGINT && g_minishell.is_in_loop == 4)
	{
		ft_putstr_fd("\n", 1);
	}
}

void	ft_status_child(int wstatus)
{
	if (WIFEXITED(wstatus))
		g_minishell.status = WEXITSTATUS(wstatus);
	if (WIFSIGNALED(wstatus))
	{
		g_minishell.status = WTERMSIG(wstatus);
		if (g_minishell.status != 131)
			g_minishell.status += 128;
	}
	if (g_minishell.status == 131)
		ft_putstr_fd("Quit (core dumped)\n", 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:43:25 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/15 15:51:34 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell	g_minishell;

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;

	(void) argv;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	if (argc != 1)
	{
		ft_putendl_fd("No argument requiered", 2);
		exit(1);
	}
	ft_init_envcpy(&shell);
	ft_create_lst_env(&shell, envp);
	ft_getexport(&shell);
	ft_init_prompt(&shell);
	return (0);
}

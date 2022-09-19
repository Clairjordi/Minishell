/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:43:25 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/19 18:31:49 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_cmds	cmds;

	//(void) argc;
	(void) argv;
	(void) envp;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	if (argc != 1)
	{
		ft_putendl_fd("No argument requiered", 2);
		exit(1);
	}
	ft_init_shell(&shell, &cmds);
	
	/* shell.test_add_env = argv[1]; */
	/* if (shell.test_add_env != NULL) */
	/* 	ft_add_envp(envp, &shell); */
	/* ft_print_envp(envp, &shell); */
	/* ft_printf("-----------------------------------\n"); */
	/* ft_print_export(envp, &shell); */
	
	ft_init_prompt(&shell, &cmds);
	ft_free_shell(&shell);
	//ft_free_cmds(cmds);
	return (0);
}

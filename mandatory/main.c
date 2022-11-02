/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:43:25 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/01 12:50:38 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argv;
	//shell.built = malloc(sizeof(t_built));
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	if (argc != 1)
	{
		ft_putendl_fd("No argument requiered", 2);
		exit(1);
	}
	//ft_init_built(&shell, envp);
	ft_init_prompt(&shell, envp);
	return (0);
}

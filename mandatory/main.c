/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:43:25 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/09 11:02:01 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argv;
	(void)argc;
	shell.built = malloc(sizeof(t_built));
	shell.built->env = NULL;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	if (argc != 1)
	{
		ft_putendl_fd("No argument requiered", 2);
		exit(1);
	}
	ft_init_envcpy(&shell);
	ft_create_lst_env(&shell, envp);
	ft_recup_env(&shell);
	//ft_print_env(&shell);
	ft_init_prompt(&shell, envp);
	ft_free_envcpy(&shell);
	ft_free_built(&shell);
	return (0);
}

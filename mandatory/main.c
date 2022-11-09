/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:43:25 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/09 17:31:47 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global g_g;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argv;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	if (argc != 1)
	{
		ft_putendl_fd("No argument requiered", 2);
		exit(1);
	}
	ft_init_built(&shell);
	ft_init_envcpy(&shell);
	ft_create_lst_env(&shell, envp);
	/* mettre ft_recup_env dans parsing, en dessous de ft_minishell pour qu'ils soit a jour */
	ft_recup_env(&shell); 
	ft_init_prompt(&shell, envp);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:43:25 by clorcery          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/10 10:22:36 by clorcery         ###   ########.fr       */
=======
/*   Updated: 2022/11/10 10:30:09 by mcloarec         ###   ########.fr       */
>>>>>>> df61538a6c455b738f6575f25c96ecb6fbdbfa1e
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
<<<<<<< HEAD
	//ft_init_built(&shell);
=======
>>>>>>> df61538a6c455b738f6575f25c96ecb6fbdbfa1e
	ft_init_envcpy(&shell);
	ft_create_lst_env(&shell, envp);
	ft_init_prompt(&shell, envp);
	return (0);
}

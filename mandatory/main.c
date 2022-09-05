/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:43:25 by clorcery          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/05 14:42:33 by clorcery         ###   ########.fr       */
=======
/*   Updated: 2022/09/05 14:21:26 by clorcery         ###   ########.fr       */
>>>>>>> clairjordi
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
void	handler(int sig, t_shell shell)
{
	if (sig == SIGINT)
	{
		ft_free();
		exit(0);
	}
}
=======
/* void	handler(int sig, t_shell shell) */
/* { */
/* 	if (sig == SIGINT) */
/* 	{ */
/* 		ft_free(); */
/* 		exit(0); */
/* 	} */
/* } */
>>>>>>> clairjordi

int	main(int argc, char *argv[])
{
	t_shell	shell;
	char	*end;


	(void) argc;
	(void) argv;
	end = "fin\n";
<<<<<<< HEAD
	signal(SIGINT, handler);
=======
//	signal(SIGINT, handler);
>>>>>>> clairjordi
	while (1)
	{
		write(1, "$>", 2);
		shell.str = get_next_line(0);
		/* str = readline ("$>"); */
		/* if (!str) */
		/* { */
		/* 	free(str); */
		/* 	exit (1); */
		/* } */
		/* add_history(str); */
		if (!ft_strcmp(shell.str, end))
		{
			free(shell.str);
			exit(0);
		}
		free(shell.str);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:43:25 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/05 18:55:55 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_shell	shell;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{	
		while (1)
		{
			shell.str = readline ("$>");
			if (!shell.str)
			{
				ft_putstr_fd("exit", 1);
				exit (1);
			}
			if (shell.str)
				add_history(shell.str);
			free(shell.str);
		}
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}

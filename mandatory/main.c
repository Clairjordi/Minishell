/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:43:25 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/09 14:09:24 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_envp(char **envp, t_shell *shell, char *opt)
{
	int		i;

	i = 0;
	if (ft_strcmp(opt, "env") == 0)
		ft_recup_env(envp, shell);
	else if (ft_strcmp(opt, "export") == 0)
		ft_export(envp, shell);
	while (shell->copy_envp[i] != NULL)
	{
		ft_printf("%s\n", shell->copy_envp[i]);
		i++;
	}
	ft_free_shell(shell);
}

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
	ft_init_shell(&shell);
	ft_print_envp(envp, &shell, "export");
	//init_prompt();
	return (0);
}

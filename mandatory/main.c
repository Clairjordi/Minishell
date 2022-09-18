/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:43:25 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/18 17:35:58 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_envp_export(char **envp, t_shell *shell, char *opt)
{
	int		i;
	char	**tmp;

	i = 0;
	if (!shell->copy_envp && ft_strcmp(opt, "env") == 0)
		ft_recup_env(envp, shell);
	else if (!shell->copy_export && ft_strcmp(opt, "export") == 0)
		ft_export(envp, shell);
	if (ft_strcmp(opt, "env") == 0)
		tmp = shell->copy_envp;
	else if (ft_strcmp(opt, "export") == 0)
		tmp = shell->copy_export;
	while (tmp[i] != NULL)
	{
		ft_printf("%s\n", tmp[i]);
		i++;
	}
	free(tmp);
	//ft_free_shell(shell); on ne peut pas free car on peut rappeller env et export plusieurs fois et si l'on a ajoute une variable, elle doit s'afficher a chaque fois
}

void	ft_print_envp(char **envp, t_shell *shell)
{
	int		i;

	i = 0;
	if (!shell->copy_envp)
		ft_recup_env(envp, shell);
	while (shell->copy_envp[i] != NULL)
	{
		ft_printf("%s\n", shell->copy_envp[i]);
		i++;
	}
}

void	ft_print_export(char **envp, t_shell *shell)
{
	int		i;

	i = 0;
	if (!shell->copy_export)
		ft_export(envp, shell);
	while (shell->copy_export[i] != NULL)
	{
		ft_printf("%s\n", shell->copy_export[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argc;
	(void) argv;
	(void) envp;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	/* if (argc != 1) */
	/* { */
	/* 	ft_putendl_fd("No argument requiered", 2); */
	/* 	exit(1); */
	/* } */
	ft_init_shell(&shell);
	/*
	shell.test_add_env = argv[1];
	ft_print_envp(envp, &shell);
	if (shell.test_add_env != NULL)
		ft_add_envp(envp, &shell);
	ft_printf("---------------------------------------------------------\n");
	ft_print_export(envp, &shell);
	*/
	init_prompt();
	ft_free_shell(&shell);
	return (0);
}

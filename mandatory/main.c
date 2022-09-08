/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:43:25 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/08 19:04:49 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_recup_env(char **envp, t_shell *shell)
{
	int	i;
	int	len_double_array;

	i = 0;
	len_double_array = 0;
	while (envp[len_double_array] != NULL)
		len_double_array++;
	shell->copy_envp = ft_calloc(sizeof(char *), (len_double_array + 1));
	if (!shell->copy_envp)
		ft_error("Malloc");
	while (envp[i] != NULL)
	{
		shell->copy_envp[i] = ft_strdup(envp[i]);
		if (shell->copy_envp[i] == NULL)
		{
			ft_free_shell(shell);
			ft_error("Malloc");
		}
		i++;
	}
	shell->copy_envp[i] = NULL;
}

void	ft_sort_export(t_shell *shell)
{
	int		i;
	char	*tmp;
	int		j;

	i = 0;
	while (shell->copy_envp[i] != NULL)
	{
		j = i + 1;
		while (shell->copy_envp[j] != NULL)
		{
			if (ft_strncmp(shell->copy_envp[i], shell->copy_envp[j], 13) > 0)
			{
				tmp = shell->copy_envp[j];
				shell->copy_envp[j] = shell->copy_envp[i];
				shell->copy_envp[i] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_export(char **envp, t_shell *shell)
{
	int	i;

	i = 0;
	ft_recup_env(envp, shell);
	ft_sort_export(shell);
	while (envp[i] != NULL)
	{
		shell->copy_envp[i] = ft_strjoin("declare -x ", shell->copy_envp[i]);
		if (shell->copy_envp[i] == NULL)
		{
			ft_free_shell(shell);
			ft_error("Malloc");
		}
		i++;
	}
}

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
	//ft_print_env(envp, &shell);
	//init_prompt();
	return (0);
}

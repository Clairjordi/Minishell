/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:33:44 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/24 16:38:25 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_shell(t_shell *shell)
{
	shell->copy_envp = NULL;
	shell->copy_export = NULL;
	shell->tab_cmd = NULL;
	shell->fill_lst = 0;
}

void	ft_init_cmds(t_cmds *cmds)
{
	cmds->prev = NULL;
	cmds->next = NULL;
	cmds->value = NULL;
	cmds->opt = NULL;
	cmds->infile = -1;
	cmds->outfile = -1;
	cmds->heredoc = '\0';
	cmds->dollar = '\0';
	cmds->pipe = -1;
	cmds->pipe_fd[2] = -1;
	cmds->cmd_path = NULL;
	cmds->quote = '\0';
}

void	ft_init_struct(t_shell *shell, t_cmds *cmds)
{
	ft_init_shell(shell);
	ft_init_cmds(cmds);
}

void	ft_init_prompt(t_shell *shell, t_cmds *cmds, char **envp)
{
	char	*str;

	while (1)
	{
		str = readline ("$>");
		if (!str || !ft_strncmp("exit", str, 4))
		{
			ft_putstr_fd("exit\n", 1); // manque des frees
			exit (0);
		}
		if (str)
		{
			ft_parsing(str, shell, cmds, envp);
			add_history(str);
		}
		free(str);
	}
}

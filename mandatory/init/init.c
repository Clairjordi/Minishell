/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:33:44 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/27 11:36:21 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_shell(t_shell *shell)
{
	shell->arg = NULL;
	shell->argc = 1;
	shell->copy_envp = NULL;
	shell->copy_export = NULL;
	shell->tab_cmd = NULL;
}

void	ft_init_cmds(t_cmds *cmd)
{
	cmd->prev = NULL;
	cmd->next = NULL;
	cmd->value = NULL;
	cmd->opt = NULL;
	cmd->infile = -1;
	cmd->outfile = -1;
	cmd->heredoc = '\0';
	cmd->dollar = '\0';
	cmd->pipe = -1;
	cmd->pipe_fd[2] = -1;
	cmd->cmd_path = NULL;
	cmd->quote = '\0';
}

void	ft_init_prompt(t_shell *shell, char **envp)
{
	char	*str;

	while (1)
	{
		str = readline ("$>");
		if (!str || !ft_strncmp("exit", str, 4))
		{
			ft_putstr_fd("exit\n", 1);
			exit (0);
		}
		if (str)
		{
			ft_parsing(str, shell, envp);
			add_history(str);
		}
		free(str);
	}
}

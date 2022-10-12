/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:33:44 by clorcery          #+#    #+#             */
/*   Updated: 2022/10/12 17:16:17 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_shell(t_shell *shell)
{
	shell->arg = NULL;
	shell->argc = 1;
	shell->quote = 0;
	shell->dollar = 0;
	shell->tmp = NULL;
	shell->tab_cmd = NULL;
	shell->copy_envp = NULL;
	shell->copy_export = NULL;
}

void	ft_init_cmds(t_cmds *cmd)
{
	cmd->cmd = NULL;
	cmd->value = NULL;
	cmd->value_split = NULL;
	cmd->infile = -1;
	cmd->outfile = -1;
	cmd->heredoc = '\0';
	cmd->pipe_fd[2] = -1;
	cmd->cmd_path = NULL;
	cmd->prev = NULL;
	cmd->next = NULL;
}

void	ft_init_prompt(t_shell *shell)
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
			ft_parsing(str, shell);
			add_history(str);
		}
		free(str);
	}
}

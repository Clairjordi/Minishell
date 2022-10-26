/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:33:44 by clorcery          #+#    #+#             */
/*   Updated: 2022/10/24 15:36:25 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_shell(t_shell *shell)
{
	shell->arg = NULL;
	shell->exec = malloc(sizeof(t_exec));
	shell->quote = 0;
	shell->dollar = 0;
	shell->pipe = 0;
	shell->tmp = NULL;
	shell->path = NULL;
	shell->tab_cmd = NULL;
	shell->copy_envp = NULL;
	shell->copy_export = NULL;
}

void	ft_init_exec(t_shell *shell)
{
	shell->exec->cmd = NULL;
	shell->exec->infile = 0;
	shell->exec->fd_in = NULL;
	shell->exec->outfile = 0;
	shell->exec->fd_out = NULL;
	shell->exec->cmd_path = NULL;
}

void	ft_init_cmds(t_cmds *cmd)
{
	cmd->value = NULL;
	cmd->value_split = NULL;
	cmd->idx_hdoc = 0;
	cmd->hdoc = FALSE;
	cmd->count_hdoc = 0;
	cmd->prev = NULL;
	cmd->next = NULL;
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
			ft_init_shell(shell);
			ft_init_exec(shell);
			ft_parsing(str, shell, envp);
			add_history(str);
		}
		free(str);
	}
}

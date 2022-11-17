/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:33:44 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/17 09:48:07 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_shell(t_shell *shell)
{
	shell->arg = NULL;
	shell->exec = malloc(sizeof(t_exec));
	if (!shell->exec)
		ft_free_malloc(shell);
	shell->built = malloc(sizeof(t_built));
	if (!shell->built)
		ft_free_malloc(shell);
	shell->pid_hdoc = 0;
	shell->quote = 0;
	shell->dollar = 0;
	shell->pipe = 0;
	shell->tab_pid = NULL;
	shell->tmp = NULL;
	shell->path = NULL;
	shell->tab_cmd = NULL;
}

void	ft_init_exec(t_shell *shell)
{
	shell->exec->cmd = NULL;
	shell->exec->infile = 0;
	shell->exec->outfile = 0;
	shell->exec->cmd_path = NULL;
	shell->exec->builtins = NULL;
	shell->exec->is_dir = 0;
}

void	ft_init_cmds(t_cmds *cmd)
{
	cmd->value = NULL;
	cmd->value_split = NULL;
	cmd->idx_hdoc = 0;
	cmd->hdoc = FALSE;
	cmd->count_hdoc = 0;
	cmd->pipe_fd[0] = 0;
	cmd->pipe_fd[1] = 0;
	cmd->cmd_found = TRUE;
	cmd->prev = NULL;
	cmd->next = NULL;
}

void	ft_init_prompt(t_shell *shell)
{
	char	*str;

	while (1)
	{
		str = readline ("$>");
		if (!str || ft_strcmp("exit", str) == 0)
		{
			ft_free_envcpy(shell);
			ft_putstr_fd("exit\n", 1);
			exit (g_minishell.status);
		}
		if (str)
		{
			ft_init_shell(shell);
			ft_init_built(shell);
			ft_init_exec(shell);
			ft_parsing(str, shell);
			add_history(str);
		}
		free(str);
	}
}

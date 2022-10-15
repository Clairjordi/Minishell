/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:33:44 by clorcery          #+#    #+#             */
/*   Updated: 2022/10/15 17:48:43 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_shell(t_shell *shell)
{
	shell->arg = NULL;
	shell->quote = 0;
	shell->dollar = 0;
	shell->tmp = NULL;
	shell->path = NULL;
	shell->tab_cmd = NULL;
	shell->copy_envp = NULL;
	shell->copy_export = NULL;
}

void	ft_init_cmds(t_cmds *cmd)
{
	cmd->cmd = NULL;
	cmd->value = NULL;
	cmd->value_split = NULL;
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->redir_l = 0;
	cmd->redir_r = 0;
	cmd->heredoc = 0;
	cmd->append = 0;
	cmd->pipe_fd[2] = -1;
	cmd->cmd_path = NULL;
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
			ft_parsing(str, shell, envp);
			add_history(str);
		}
		free(str);
	}
}

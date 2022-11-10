/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:33:44 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/10 17:18:42 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_shell(t_shell *shell)
{
	shell->arg = NULL;
	shell->exec = malloc(sizeof(t_exec));
	shell->built = malloc(sizeof(t_built));
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

int	ft_exit(t_shell *shell, char *str)
{
	char	*arg;
	int		size;

	(void) shell;
	size = ft_strlen(str);
	if (ft_strncmp("exit", str, 4) == 0)
	{
		arg = ft_substr(str, 5, (size - 5));
		if (arg == NULL)
			ft_free_malloc(shell);
		g_g.status = ft_atoi(arg);
		free(arg);
		return (TRUE);
	}
	return (FALSE);
}

void	ft_init_prompt(t_shell *shell)
{
	char	*str;

	while (1)
	{
		str = readline ("$>");
		if (!str || ft_exit(shell, str) == TRUE/*!ft_strncmp("exit", str, 4)*/)
		{
			ft_free_envcpy(shell); // changer free_last_built pour ctrl +D
			ft_putstr_fd("exit\n", 1);
			exit (g_g.status);
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

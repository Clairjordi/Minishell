/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:36:41 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/10 11:08:03 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free(t_shell *shell, char *s)
{	
	ft_free_cmds(shell);
	if (shell->exec != NULL)
		ft_free_exec(shell);
	ft_free_shell(shell);
	if (s != NULL)
		perror(s);
}

void	ft_free_exec(t_shell *shell)
{	
	if (shell->exec->cmd != NULL)
		shell->exec->cmd = ft_free_tab_char(shell->exec->cmd);
	if (shell->exec->cmd_path != NULL)
	{
		free(shell->exec->cmd_path);
		shell->exec->cmd_path = NULL;
	}
	if (shell->exec->builtins != NULL)
		shell->exec->builtins = ft_free_tab_char(shell->exec->builtins);
	shell->exec->infile = 0;
	shell->exec->outfile = 0;
	shell->exec->is_dir = 0;
}

void	ft_free_cmds(t_shell *shell)
{
	t_cmds	*tmp;
	t_cmds	*buf;

	if (shell->arg == NULL)
		return ;
	tmp = shell->arg;
	while (tmp != NULL)
	{
		buf = tmp->next;
		if (tmp->value != NULL)
			free(tmp->value);
		if (tmp->value_split != NULL)
			ft_free_tab_char(tmp->value_split);
		if (tmp->hdoc == TRUE)
			unlink(".heredoc");
		free(tmp);
		tmp = buf;
	}
	shell->arg = NULL;
}

void	ft_free_shell(t_shell *shell)
{
	if (shell->tab_pid != NULL)
		ft_free_tab_char(shell->tab_pid);
	if (shell->tmp != NULL)
	{
		free(shell->tmp);
		shell->tmp = NULL;
	}
	if (shell->tab_cmd != NULL)
		shell->tab_cmd = ft_free_tab_char(shell->tab_cmd);
	if (shell->path != NULL)
		shell->path = ft_free_tab_char(shell->path);
	if (shell->exec != NULL)
	{
		free(shell->exec);
		shell->exec = NULL;
	}
}

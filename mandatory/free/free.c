/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:36:41 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/24 22:47:20 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free(t_shell *shell, char *s)
{
	ft_free_shell(shell);
	ft_free_cmds(shell);
	if (s != NULL)
		perror(s);
}

void	ft_free_cmds(t_shell *shell)
{
	t_cmds	*tmp;
	t_cmds	*buf;

	/* while (cmds->prev != NULL) */
	/* 	cmds = cmds->prev; */
	tmp = shell->arg;
	if (shell->arg == NULL)
		return ;
	while (tmp != NULL)
	{
		buf = tmp->next;
		free(tmp->value);
		free(tmp);
		tmp = buf;
	}
	shell->arg = NULL;
}

void	ft_free_shell(t_shell *shell)
{
	if (shell->copy_envp != NULL)
		ft_free_tab_char(shell->copy_envp);
	if (shell->copy_export != NULL)
		ft_free_tab_char(shell->copy_export);
	if (shell->tab_cmd != NULL)
		ft_free_tab_char(shell->tab_cmd);
}

void	ft_free_malloc(t_shell *shell)
{
	ft_free_shell(shell);
	ft_free_cmds(shell);
	ft_error("Malloc error");
}

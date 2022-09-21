/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:36:41 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/21 17:44:04 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_error(t_shell *shell, t_cmds *cmds, char *s)
{
	ft_free_shell(shell);
	ft_free_cmds(cmds);
	if (s != NULL)
		ft_error(s);
}

void	ft_free_cmds(t_cmds *cmds)
{
	t_cmds	*tmp;
	t_cmds	*buf;

	tmp = cmds;
	if (cmds == NULL)
		return ;
	while (tmp != NULL)
	{
		buf = tmp->next;
		free(tmp);
		tmp = buf;
	}
	cmds = NULL;
}

void	ft_free_shell(t_shell *shell)
{
	if (shell->copy_envp != NULL)
		ft_free_tab_char(shell->copy_envp);
	if (shell->copy_export != NULL)
		ft_free_tab_char(shell->copy_export);
}

void	ft_free_malloc(t_shell *shell)
{
	ft_free_shell(shell);
	ft_error("Malloc");
}

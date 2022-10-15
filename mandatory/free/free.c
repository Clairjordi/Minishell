/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:36:41 by clorcery          #+#    #+#             */
/*   Updated: 2022/10/15 17:27:06 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free(t_shell *shell, char *s)
{	
	ft_free_cmds(shell);
	ft_free_shell(shell);
	if (s != NULL)
		perror(s);
}

void	ft_free_cmds(t_shell *shell)
{
	t_cmds	*tmp;
	t_cmds	*buf;

	tmp = shell->arg;
	if (shell->arg == NULL)
		return ;
	while (tmp != NULL)
	{
		buf = tmp->next;
		free(tmp->value);
		ft_free_tab_char(tmp->value_split);
		if (tmp->cmd_path != NULL)
			free(tmp->cmd_path);
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
	if (shell->tab_cmd != NULL)
		ft_free_tab_char(shell->path);
}

void	ft_free_malloc(t_shell *shell)
{
	ft_free_shell(shell);
	ft_free_cmds(shell);
	ft_error("Malloc error");
}

void	*ft_free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

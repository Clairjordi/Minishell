/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:50:01 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/17 13:00:01 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_malloc(t_shell *shell)
{
	ft_free_envcpy(shell);
	ft_free_cmds(shell);
	ft_free_shell(shell);
	ft_error("Malloc error");
}

void	*ft_free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	ft_free_close(t_shell *shell)
{
	if (shell->exec->infile > 2)
		close(shell->exec->infile);
	if (shell->exec->outfile > 2)
		close(shell->exec->outfile);
	if (shell->exec != NULL)
		ft_free_exec(shell);
}

void	ft_free_close_pipe(t_shell *shell, t_cmds *lst)
{
	if (shell->exec->infile > 2)
		close(shell->exec->infile);
	if (shell->exec->outfile > 2)
		close(shell->exec->outfile);
	if (shell->exec != NULL)
		ft_free_exec(shell);
	if (lst-> prev != NULL && lst->prev->pipe_fd[0] > 2)
		close(lst->prev->pipe_fd[0]);
	if (lst-> prev != NULL && lst->prev->pipe_fd[1] > 2)
		close(lst->prev->pipe_fd[1]);
}

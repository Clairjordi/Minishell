/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:50:01 by clorcery          #+#    #+#             */
/*   Updated: 2022/10/31 19:15:16 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	ft_free_close(t_shell *shell)
{
	if (shell->exec->infile > 2)
		close(shell->exec->infile);
	if (shell->exec->outfile > 2)
		close(shell->exec->outfile);
	if (shell->exec != NULL)
		ft_free_exec(shell);
}

int	ft_verif_cat_b(t_shell *shell, t_cmds *lst)
{
	if (ft_strcmp(lst->value_split[0], "cat") == 0)
	{
		if (shell->exec->infile == 0 && shell->exec->outfile == 0)
			return (FALSE);
	}
	return (TRUE);
}

void	ft_free_close_pipe(t_shell *shell, t_cmds *lst)
{
	if (shell->exec->infile > 2)
		close(shell->exec->infile);
	if (shell->exec->outfile > 2)
		close(shell->exec->outfile);
	if (shell->exec != NULL)
		ft_free_exec(shell);
	/* if (lst->next == NULL) */
	/* 	close(lst->prev->pipe_fd[0]); */
	if (lst->prev != NULL)
	{
		if (lst->prev->pipe_fd[0] > 2 && ft_verif_cat_b(shell, lst) == TRUE)
		{
			close(lst->prev->pipe_fd[0]);
			lst->prev->pipe_fd[0] = 0;
		}

		if (lst->next == NULL)
		{
			if (lst->pipe_fd[0] > 2)
				close(lst->pipe_fd[0]);
			if (lst->pipe_fd[1] > 2)
				close(lst->pipe_fd[1]);
		}
	}
	if (lst->next != NULL && lst->hdoc == FALSE /*&& lst->next->hdoc == TRUE*/)
	{
		if (ft_strcmp(lst->value_split[0], "cat") != 0)
		{
	 		close(lst->pipe_fd[0]);
			lst->pipe_fd[0] = 0;
		}
		else if (ft_strcmp(lst->value_split[0], "cat") == 0 
				&& (shell->exec->infile > 2 || shell->exec->outfile > 2))
		{
	 		close(lst->pipe_fd[0]);
			lst->pipe_fd[0] = 0;
		}
	}
	if (lst->prev != NULL && lst->prev->hdoc == TRUE
			&& lst->prev->prev != NULL && lst->prev->prev->hdoc == TRUE
			&& ft_strcmp(lst->value_split[0], "cat") == 0)
	{
		if (shell->exec->infile == 0 && shell->exec->outfile == 0)
		{	
			close(lst->prev->prev->pipe_fd[0]);
			lst->prev->prev->pipe_fd[0] = 0;
		}
	}
	else if (lst->prev != NULL && lst->prev->prev != NULL
			&& ft_strcmp(lst->value_split[0], "cat") == 0)
	{
		if (shell->exec->infile == 0 && shell->exec->outfile == 0)
		{	
			close(lst->prev->prev->pipe_fd[0]);
			lst->prev->prev->pipe_fd[0] = 0;
		}
	}
}

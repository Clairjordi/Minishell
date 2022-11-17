/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:56:35 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/17 17:06:58 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_sort_check_built(t_shell *shell, t_cmds *lst, int *i)
{
	if ((*i == 0
			|| (*i > 0 && ft_valid_redirect(lst->value_split[*i - 1]) == FALSE))
		&& shell->exec->cmd == NULL)
	{
		if (ft_check_is_builtins(shell, lst->value_split, i) == TRUE)
			return (TRUE);
	}
	return (FALSE);
}

static void	ft_sort_cmd_bis(t_shell *shell, t_cmds *lst)
{
	int	i;

	i = 0;
	while (lst->value_split[i])
	{
		if (ft_sort_check_built(shell, lst, &i) == TRUE)
			break ;
		if (shell->exec->is_dir == 0 && shell->exec->outfile != -1)
			shell->exec->is_dir = ft_is_directory(lst->value_split[i]);
		if (ft_check_infile(shell->exec, lst->value_split, &i) == FALSE)
			break ;
		if (lst->hdoc == TRUE && lst->value_split[i + 1] == NULL)
		{
			if (shell->exec->infile > 2)
				close(shell->exec->infile);
			shell->exec->infile = open(".heredoc", O_RDONLY, 0644);
		}
		if (ft_check_outfile(shell, lst->value_split, i) == FALSE)
			break ;
		if (shell->exec->builtins == NULL && shell->exec->is_dir == 0
			&& lst->cmd_found == TRUE && lst->value_split[i] != NULL)
			lst->cmd_found = ft_check_cmd(shell, lst->value_split, i);
		if (lst->value_split[i] != NULL)
			i++;
	}
}

void	ft_sort_cmd(t_shell *shell, t_cmds *lst)
{
	int	wstatus;

	wstatus = 0;
	ft_sort_cmd_bis(shell, lst);
	if (shell->exec->builtins != NULL
		&& ft_check_builtins_without_fork(shell) == TRUE)
	{
		ft_free_close(shell);
		return ;
	}
	if ((shell->exec->cmd != NULL || shell->exec->builtins != NULL)
		&& shell->exec->outfile != -1)
	{
		wstatus = ft_execute_cmd(shell, wstatus);
		ft_status_child(wstatus);
	}
	ft_free_close(shell);
}

static void	ft_sort_cmd_pipe_bis(t_shell *shell, t_cmds *lst)
{
	if (shell->exec->builtins != NULL || shell->exec->cmd != NULL)
		ft_execute_pipe(shell, shell->exec, lst);
	ft_free_close_pipe(shell, lst);
}

void	ft_sort_cmd_pipe(t_shell *shell, t_cmds *lst)
{
	int	i;

	i = 0;
	while (lst->value_split[i])
	{
		if (ft_sort_check_built(shell, lst, &i) == TRUE)
			break ;
		if (shell->exec->is_dir == 0 && shell->exec->cmd == NULL)
			shell->exec->is_dir = ft_is_directory(lst->value_split[i]);
		if (ft_check_infile(shell->exec, lst->value_split, &i) == FALSE)
			break ;
		if (lst->hdoc == TRUE && lst->value_split[i + 1] == NULL)
		{
			if (shell->exec->infile > 2)
				close(shell->exec->infile);
			shell->exec->infile = open(".heredoc", O_RDONLY, 0644);
		}
		if (ft_check_outfile(shell, lst->value_split, i) == FALSE)
			break ;
		if (shell->exec->is_dir == 0 && lst->cmd_found == TRUE)
			lst->cmd_found = ft_check_cmd(shell, lst->value_split, i);
		if (lst->value_split[i] != NULL)
			i++;
	}
	ft_sort_cmd_pipe_bis(shell, lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:56:35 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/09 19:09:32 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_sort_cmd_bis(t_shell *shell, t_cmds *lst, char **envp)
{
	int	i;

	i = 0;
	while (lst->value_split[i])
	{
		if (ft_check_is_builtins(shell, lst->value_split, &i) == TRUE)
			break ;
		if (shell->exec->is_dir == 0)
			shell->exec->is_dir = ft_is_directory(lst->value_split[i]);
		if (ft_check_infile(shell->exec, lst->value_split, i) == FALSE)
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
			&& lst->cmd_found == TRUE)
			lst->cmd_found = ft_check_cmd(shell, envp, lst->value_split, i);
		if (lst->value_split[i] != NULL)
			i++;
	}
}

void	ft_sort_cmd(t_shell *shell, t_cmds *lst, char **envp)
{
	int	wstatus;

	wstatus = 0;
	ft_sort_cmd_bis(shell, lst, envp);
	if (shell->exec->builtins != NULL
		&& ft_check_builtins_without_fork(shell) == TRUE)
	{
		ft_free_close(shell);
		return ;
	}
	if (shell->exec->cmd != NULL || shell->exec->builtins != NULL)
	{
		wstatus = ft_execute_cmd(shell, envp, wstatus);
		ft_status_child(wstatus);
	}
	ft_free_close(shell);
}

static void	ft_sort_cmd_pipe_bis(t_shell *shell, t_cmds *lst, char **envp)
{
	if (shell->exec->cmd != NULL || shell->exec->builtins != NULL)
		ft_execute_pipe(shell, shell->exec, envp, lst);
	ft_free_close_pipe(shell, lst);
}

void	ft_sort_cmd_pipe(t_shell *shell, t_cmds *lst, char **envp)
{
	int	i;

	i = 0;
	while (lst->value_split[i])
	{	
		if (ft_check_is_builtins(shell, lst->value_split, &i) == TRUE)
			break ;
		if (shell->exec->is_dir == 0)
			shell->exec->is_dir = ft_is_directory(lst->value_split[i]);
		if (ft_check_infile(shell->exec, lst->value_split, i) == FALSE)
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
			lst->cmd_found = ft_check_cmd(shell, envp, lst->value_split, i);
		if (lst->value_split[i] != NULL)
			i++;
	}
	ft_sort_cmd_pipe_bis(shell, lst, envp);
}

void	ft_check_execute(t_shell *shell, char **envp)
{
	t_cmds	*lst;

	lst = shell->arg;
	shell->exec->pid = 0;
	if (shell->pipe == 1)
		ft_sort_cmd(shell, lst, envp);
	else
	{
		while (lst)
		{
			if (lst->next != NULL)
			{
				shell->pipe = ft_check_shell_pipe(shell, lst);
				if (shell->pipe == ERROR)
					break ;
			}
			ft_sort_cmd_pipe(shell, lst, envp);
			ft_add_pid(shell);
			lst = lst->next;
		}
		ft_waitpid_pipe(shell);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:56:35 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/03 12:19:09 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_sort_cmd(t_shell *shell, t_exec *exec, t_cmds *lst, char **envp)
{
	int	i;
	int	wstatus;
	
	i = 0;
	wstatus = 0;
	while (lst->value_split[i])
	{
		if (ft_check_infile(exec, lst->value_split, i) == FALSE)
			break ;
		if (lst->hdoc == TRUE && lst->value_split[i + 1] == NULL)
		{
			if (shell->exec->infile > 2)
				close(shell->exec->infile);
			shell->exec->infile = open(".heredoc", O_RDONLY, 0644);
		}
		if (ft_check_outfile(shell, lst->value_split, i) == FALSE)
			break ;
		ft_check_cmd(shell, envp, lst->value_split, i);
		if (lst->value_split[i] != NULL)
			i++;
	}
	if (shell->exec->cmd != NULL)
		wstatus = ft_execute_cmd(shell, envp, lst, wstatus);
	ft_free_close(shell);	
	ft_status_child(wstatus);
	if (wstatus == 2)
	{
		ft_putstr_fd("\n", 1);
		return (ERROR);
	}
	return (0);
}

int	ft_sort_cmd_pipe(t_shell *shell, t_cmds *lst, char **envp)
{
	int	i;
	
	i = 0;
	while (lst->value_split[i])
	{
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
		ft_check_cmd(shell, envp, lst->value_split, i);
		if (lst->value_split[i] != NULL)
			i++;
	}
	if (shell->exec->cmd != NULL)
		ft_execute_pipe(shell, shell->exec, envp, lst);
	ft_free_close_pipe(shell, lst);
	return (0);
}

int	ft_check_execute(t_shell *shell, char **envp)
{
	t_cmds	*lst;

	lst = shell->arg;
	shell->exec->pid = 0;
	if (shell->pipe == 1)
	{
		if (ft_sort_cmd(shell, shell->exec, lst, envp)== ERROR)
			return (ERROR);
	}
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
		if (g_g.status != 127)
		{
			if (ft_waitpid_pipe(shell) == ERROR)
				return (ERROR);
		}
	}
	return (0);
}

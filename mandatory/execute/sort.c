/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:56:35 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/01 12:08:37 by clorcery         ###   ########.fr       */
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
		if (lst->hdoc == FALSE)
		{
			if (ft_check_first(shell, envp, lst->value_split[0]) == 0 && i == 0)
				break ;
			if (ft_check_infile(exec, lst->value_split, i) == FALSE)
				break ;
		}
		else if (lst->hdoc == TRUE)
		{
			if (i > 0 && ft_strcmp(lst->value_split[i - 1], "<") == 0)
			{
				ft_check_infile(shell->exec, lst->value_split, i);
				if (shell->exec->infile > 2)
					close(shell->exec->infile);
			}
			if (lst->value_split[i + 1] == NULL)
			{
				if (shell->exec->infile > 2)
					close(shell->exec->infile);
				shell->exec->infile = open(".heredoc", O_RDONLY, 0644);
			}
		}
		if (ft_check_outfile(shell, lst->value_split, i) == FALSE)
			break ;
		if (ft_check_cmd(shell, envp, lst->value_split, i) == FALSE)
			break ;
		if (lst->value_split[i] != NULL)
			i++;
	}
	if (shell->exec->cmd != NULL)
		wstatus = ft_execute_cmd(shell, envp, lst, wstatus);
	ft_free_close(shell);	
	ft_status_child(wstatus);
	if (wstatus != 0)
	{
		ft_putstr_fd("\n", 1);
		return (ERROR);
	}
	return (0);
}

int	ft_verif_cat(t_shell *shell, t_cmds *lst)
{
	if (ft_strcmp(lst->value_split[0], "cat") == 0 && lst->prev != NULL
			&& lst->prev->hdoc == TRUE)
	{
		if (shell->exec->infile == 0 && shell->exec->outfile == 0)
			return (FALSE);
	}
	return (TRUE);
}

int	ft_sort_cmd_pipe(t_shell *shell, t_cmds *lst, char **envp)
{
	int	i;

	i = 0;
	while (lst->value_split[i])
	{
		if (lst->hdoc == FALSE)
		{
			if (ft_check_first(shell, envp, lst->value_split[0]) == FALSE
				&& i == 0)
				break ;
			if (ft_check_infile(shell->exec, lst->value_split, i) == FALSE)
				break ;
		}
		else if (lst->hdoc == TRUE)
		{
			if (i > 0 && ft_strcmp(lst->value_split[i - 1], "<") == 0)
			{
				ft_check_infile(shell->exec, lst->value_split, i);
				if (shell->exec->infile > 2)
					close(shell->exec->infile);
			}
			if (lst->value_split[i + 1] == NULL)
			{
				if (shell->exec->infile > 2)
					close(shell->exec->infile);
				shell->exec->infile = open(".heredoc", O_RDONLY, 0644);
			}
		}
		if (ft_check_outfile(shell, lst->value_split, i) == FALSE)
			break ;
		if (ft_check_cmd(shell, envp, lst->value_split, i) == FALSE)
			break ;
		if (lst->value_split[i] != NULL)
			i++;
	}
	if (shell->exec->cmd != NULL && ft_verif_cat(shell, lst) == TRUE)
		ft_execute_pipe(shell, shell->exec, envp, lst);
	ft_free_close_pipe(shell, lst);
	return (0);
}

int ft_check_cmd_pipe(t_shell *shell, t_cmds *lst, char **envp)
{
	int i;

	i = 0;
	while (lst->value_split[i])
	{
		if (ft_get_path(shell, lst->value_split[i], envp) != NULL)
			return (TRUE);
		i++;
	}
	return (FALSE);
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
			if (lst->next != NULL && ft_check_cmd_pipe(shell, lst, envp) == TRUE)
			{
				shell->pipe = ft_check_shell_pipe(shell, lst);
				if (shell->pipe == ERROR)
					break ;
			}
			ft_sort_cmd_pipe(shell, lst, envp);
			ft_add_pid(shell);
			lst = lst->next;
		}
		if (ft_waitpid_pipe(shell) == ERROR)
			return (ERROR);
	}
	return (0);
}

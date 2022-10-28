/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:56:35 by mcloarec          #+#    #+#             */
/*   Updated: 2022/10/28 11:58:18 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_sort_cmd(t_shell *shell, t_exec *exec, t_cmds *lst, char **envp)
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
			if (ft_check_infile(exec, lst->value_split, i) == FALSE)
				break ;
		}
		if (ft_check_outfile(exec, lst->value_split, i) == FALSE)
			break ;
		if (ft_check_cmd(shell, envp, lst->value_split, i) == FALSE)
			break ;
		if (lst->value_split[i] != NULL)
		i++;
	}
	if (shell->exec->cmd != NULL)
		ft_execute_cmd(shell, shell->exec, envp, lst);
	ft_free_close(shell);
}

void	ft_sort_cmd_pipe(t_shell *shell, t_cmds *lst, char **envp)
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
		if (ft_check_outfile(shell->exec, lst->value_split, i) == FALSE)
			break ;
		if (ft_check_cmd(shell, envp, lst->value_split, i) == FALSE)
			break ;
		if (lst->value_split[i] != NULL)
		i++;
	}
	if (shell->exec->cmd != NULL)
		ft_execute_pipe(shell, shell->exec, envp, lst);
	ft_free_close_pipe(shell, lst);
}

int	ft_check_shell_pipe(t_shell *shell, t_cmds *lst)
{
	if (shell->pipe > 1)
	{
		if (pipe(lst->pipe_fd) == ERROR)
		{
			perror("ERROR pipe");
			return (ERROR);
		}
		shell->pipe--;
	}
	return (shell->pipe);
}

void	ft_check_execute(t_shell *shell, char **envp)
{
	t_cmds	*lst;
	t_exec	*exec;

	lst = shell->arg;
	exec = shell->exec;
	if (shell->pipe == 1)
	{
		while (lst)
		{	
			ft_sort_cmd(shell, exec, lst, envp);
			lst = lst->next;
		}
	}
	else
	{
		while (lst)
		{
			shell->pipe = ft_check_shell_pipe(shell, lst);
			if (shell->pipe == ERROR)
				break ;
			ft_sort_cmd_pipe(shell, lst, envp);
			lst = lst->next;
		}
	}
}

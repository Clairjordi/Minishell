/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:56:35 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/05 10:32:44 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"




int	ft_check_builtins(t_shell *shell, char *str, char **tab)
{
	if (ft_strcmp(str, "pwd") == 0)
	{
		ft_pwd();
		return (TRUE);
	}
	if (ft_strcmp(str, "env") == 0)
	{
		ft_print_env(shell);
		return (TRUE);
	}
	if (ft_strcmp(str, "echo") == 0)
	{
		ft_echo(tab);
		return (TRUE);
	}
	return (FALSE);
}

static void	ft_sort_cmd_bis(t_shell *shell, t_cmds *lst, char **envp)
{
	int	i;
	int	is_dir;

	i = 0;
	is_dir = 0;
	while (lst->value_split[i])
	{
		if (ft_check_builtins(shell, lst->value_split[i], lst->value_split) == TRUE)
			break;
		is_dir = ft_is_directory(lst->value_split[i]);
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
		if (is_dir == 0 && lst->cmd_found == TRUE)
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
	if (shell->exec->cmd != NULL)
	{
		wstatus = ft_execute_cmd(shell, envp, wstatus);
		ft_status_child(wstatus);
	}
	ft_free_close(shell);
}

static void	ft_sort_cmd_pipe_bis(t_shell *shell, t_cmds *lst, char **envp)
{
	if (shell->exec->cmd != NULL)
		ft_execute_pipe(shell, shell->exec, envp, lst);
	ft_free_close_pipe(shell, lst);
}

void	ft_sort_cmd_pipe(t_shell *shell, t_cmds *lst, char **envp)
{
	int	i;
	int	is_dir;

	i = 0;
	is_dir = 0;
	while (lst->value_split[i])
	{	
		if (ft_check_builtins(shell, lst->value_split[i], lst->value_split) == TRUE)
			break;
		is_dir = ft_is_directory(lst->value_split[i]);
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
		if (is_dir == 0 && lst->cmd_found == TRUE)
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

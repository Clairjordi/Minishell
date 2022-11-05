/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:56:35 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/05 12:41:01 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_builtins(t_shell *shell, char *str, char **tab, int i, t_cmds *lst)
{
	if (ft_strcmp(str, "pwd") == 0)
	{
		ft_pwd();
		shell->exec->is_dir = 1;
		ft_printf("pwd\n");
		if (pipe(lst->pipe_fd) == ERROR)
		{
			perror("ERROR pipe");
			return (ERROR);
		}
		return (TRUE);
	}
	if (ft_strcmp(str, "env") == 0)
	{
		ft_print_env(shell);
		ft_printf("env\n");
		return (TRUE);
	}
	if (ft_strcmp(str, "echo") == 0)
	{
		ft_echo(tab);
		ft_printf("echo\n");
		return (TRUE);
	}
	if (ft_strcmp(str, "cd") == 0)
	{
		ft_cd(tab[i + 1]);
		if (tab[i + 2] != NULL)
		{
			ft_putendl_fd("bash: cd: too many arguments", 2);
			g_g.status = 1;
		}
		ft_printf("cd\n");
		shell->exec->is_dir = 1;

		return (TRUE);
	}
	return (FALSE);
}

static void	ft_sort_cmd_bis(t_shell *shell, t_cmds *lst, char **envp)
{
	int	i;

	i = 0;
	while (lst->value_split[i])
	{
		if (shell->exec->cmd == NULL)
		{
			if (ft_check_builtins(shell, lst->value_split[i], lst->value_split, i, lst) == TRUE)
				shell->exec->builtins = TRUE;
		}
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
		if (shell->exec->builtins == FALSE && shell->exec->is_dir == 0 
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
	if (shell->exec->cmd != NULL)
	{
		wstatus = ft_execute_cmd(shell, envp, wstatus);
		ft_status_child(wstatus);
	}
	else if (shell->exec->builtins == TRUE)
	{
		wstatus = ft_execute_builtins(shell, wstatus, lst);
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

	i = 0;
	while (lst->value_split[i])
	{	
		if (ft_check_builtins(shell, lst->value_split[i], lst->value_split, i, lst) == TRUE)
			break;
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

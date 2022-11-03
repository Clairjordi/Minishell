/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:56:35 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/03 17:30:08 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_a_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_directory(char *str)
{
	struct stat	*s;

	if (ft_is_a_path(str) == 1)
		return (0);
	s = malloc(sizeof(struct stat));
	if (stat(str, s) == -1)
	{
		perror(str);
		if (errno == EACCES)
			g_g.status = 126;
		else
			g_g.status = 127;
		free(s);
		return (1);
	}
	if (S_ISDIR(s->st_mode))
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": Is a directory", 2);
		g_g.status = 126;
		free(s);
		return (1);
	}
	free(s);
	return (0);
}

int	ft_sort_cmd(t_shell *shell, t_exec *exec, t_cmds *lst, char **envp)
{
	int	i;
	int	wstatus;

	i = 0;
	wstatus = 0;
	while (lst->value_split[i])
	{
		ft_is_directory(lst->value_split[i]);
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
		if (g_g.status != 126 && lst->cmd_found == TRUE)
			lst->cmd_found = ft_check_cmd(shell, envp, lst->value_split, i);
		if (lst->value_split[i] != NULL)
			i++;
	}
	if (shell->exec->cmd != NULL)
	{
		wstatus = ft_execute_cmd(shell, envp, lst, wstatus);
		ft_status_child(wstatus);
	}
	ft_free_close(shell);
	return (0);
}

int	ft_sort_cmd_pipe(t_shell *shell, t_cmds *lst, char **envp)
{
	int	i;

	i = 0;
	while (lst->value_split[i])
	{
		ft_is_directory(lst->value_split[i]);
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
		if (g_g.status != 126 && lst->cmd_found == TRUE)
			lst->cmd_found = ft_check_cmd(shell, envp, lst->value_split, i);
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
		ft_waitpid_pipe(shell);
	}
	return (0);
}

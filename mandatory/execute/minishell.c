/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:35:26 by mcloarec          #+#    #+#             */
/*   Updated: 2022/10/28 10:37:24 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_valid_redirect(char *s)
{
	if (ft_strcmp(s, "<<") == 0)
		return (1);
	if (ft_strcmp(s, "<") == 0)
		return (2);
	if (ft_strcmp(s, ">>") == 0)
		return (3);
	if (ft_strcmp(s, ">") == 0)
		return (4);
	return (FALSE);
}

int	ft_check_error_redirect(t_shell *shell)
{
	int		i;
	t_cmds	*lst;

	i = 0;
	lst = shell->arg;
	while (lst)
	{
		i = 0;
		while (lst->value_split[i] != NULL)
		{
			if (ft_valid_redirect(lst->value_split[i]) != FALSE
				&& (lst->value_split[i + 1] == NULL
					|| ft_valid_redirect(lst->value_split[i + 1]) != FALSE))
			{
				ft_free(shell, "Syntax error near unexpected token");
				g_g.status = 2;
				return (FALSE);
			}
			i++;
		}
		lst = lst->next;
	}
	return (TRUE);
}

int	ft_check_infile(t_exec *exec, char **tab, int i)
{
	if (i != 0 && ft_valid_redirect(tab[i - 1]) == 2)
	{
		if (exec->infile > 2)
			close(exec->infile);
		exec->infile = open(tab[i], O_RDONLY, 0644);
		if (exec->infile == -1)
		{
			perror("File error");
			g_g.status = 2;
			return (FALSE);
		}
	}
	return (TRUE);
}

int	ft_check_outfile(t_exec *exec, char **tab, int i)
{
	if (i != 0 && ft_valid_redirect(tab[i - 1]) == 3)
	{
		if (exec->outfile > 2)
			close(exec->outfile);
		exec->outfile = open(tab[i], (O_RDWR | O_APPEND | O_CREAT), 0644);
		if (exec->outfile == -1)
		{
			perror("File error ");
			g_g.status = 2;
			return (FALSE);
		}
	}
	else if (i != 0 && ft_valid_redirect(tab[i - 1]) == 4)
	{
		if (exec->outfile > 2)
			close(exec->outfile);
		exec->outfile = open(tab[i], (O_RDWR | O_TRUNC | O_CREAT), 0644);
		if (exec->outfile == -1)
		{
			perror("File error ");
			g_g.status = 2;
			return (FALSE);
		}
	}
	return (TRUE);
}

int	ft_check_first(t_shell *shell, char **envp, char *s)
{
	if (ft_get_path(shell, s, envp) == NULL
		&& ft_valid_redirect(s) == FALSE)
	{
		ft_putendl_fd("First arg must be cmd or redirection", 2);
		g_g.status = 127;
		return (FALSE);
	}
	return (TRUE);
}

void	ft_add_opt_arg(t_shell *shell, char *s)
{
	shell->exec->cmd = ft_realloc_tab_char(shell->exec->cmd, s);
	if (shell->exec->cmd == NULL)
		ft_free_malloc(shell);
}

int ft_add_cmd(t_shell *shell, char *s, char **envp)
{
	if (shell->exec->cmd != NULL
		&& ft_get_path(shell, s, envp) != NULL)
	{
		perror("ERROR cmd");
		g_g.status = 1;
		return (FALSE);
	}
	else if (shell->exec->cmd == NULL)
	{
		shell->exec->cmd = ft_calloc(sizeof(char *), 2);
		if (!shell->exec->cmd)
			ft_free_malloc(shell);
		shell->exec->cmd[0] = ft_strdup(shell->exec->cmd_path);
		if (shell->exec->cmd[0] == NULL)
			ft_free_malloc(shell);
		shell->exec->cmd[1] = NULL;
	}
	return (TRUE);
}

int	ft_check_cmd(t_shell *shell, char *name_cmd, char **envp, char **tab, int i)
{
	if (shell->exec->cmd_path == NULL && ft_valid_redirect(name_cmd) == FALSE)
		ft_get_path(shell, name_cmd, envp);
	if (i == 0 && ft_valid_redirect(name_cmd) == FALSE)
		ft_add_cmd(shell, name_cmd, envp);
	else if (i > 0 && shell->exec->cmd_path != NULL
		&& shell->exec->cmd == NULL
		&& ft_valid_redirect(tab[i - 1]) == FALSE
		&& ft_valid_redirect(name_cmd) == FALSE)
		ft_add_cmd(shell, name_cmd, envp);
	else if (i > 0 && shell->exec->cmd != NULL
		&& ft_valid_redirect(name_cmd) == FALSE
		&& ft_valid_redirect(tab[i - 1]) == FALSE)
		ft_add_opt_arg(shell, name_cmd);
	return (TRUE);
}

void	ft_execute_cmd(t_shell *shell, t_exec *exec, char **envp, t_cmds *lst)
{
	if (lst->hdoc == TRUE)
	{
		exec->infile = open(".heredoc", O_RDONLY, 0644);
		if (exec->infile == ERROR)
			perror("ERROR infile");
	}
	exec->pid = fork();
	if (exec->pid == ERROR)
		perror("ERROR pid");
	 if (exec->pid == 0)
	{
		if (dup2(exec->infile, STDIN_FILENO) == ERROR)
			perror("ERROR dup");
		if (exec->outfile > 2)
		{
			if (dup2(exec->outfile, STDOUT_FILENO) == ERROR)
				perror("ERROR dup");

		}
		if (execve(exec->cmd_path, exec->cmd, envp) == ERROR)
		{
			close (exec->infile);
			ft_free(shell, "ERROR execve");
			exit(1);
		}
	}
	else
	{
		if (waitpid(exec->pid, NULL, 0) == ERROR)
			perror("ERROR waitpid");
	}
}

void	ft_execute_pipe(t_shell *shell, t_exec *exec, char **envp, t_cmds *lst)
{
	if (lst->hdoc == TRUE)
	{
		exec->infile = open(".heredoc", O_RDONLY, 0644);
		if (exec->infile == ERROR)
			perror("ERROR infile");
	}
	exec->pid = fork();
	if (exec->pid == ERROR)
		perror("ERROR pid");
	if (exec->pid == 0)
	{
		if (lst->prev == NULL)
		{
			if (dup2(exec->infile, STDIN_FILENO) == ERROR)
				perror("ERROR dup 1");
			if (dup2(lst->pipe_fd[1], STDOUT_FILENO) == ERROR)
					perror("ERROR dup 2");
		}
		else if (lst->next == NULL)
		{
			if (dup2(lst->prev->pipe_fd[0], STDIN_FILENO) == ERROR)
				perror("ERROR dup 3");
			if (exec->outfile > 2)
			{
				if (dup2(exec->outfile, STDOUT_FILENO) == ERROR)
					perror("ERROR dup 4");
			}
		}
		else
		{
			if (dup2(lst->prev->pipe_fd[0], STDIN_FILENO) == ERROR)
				perror("ERROR dup 5");
			if (dup2(lst->pipe_fd[1], STDOUT_FILENO) == ERROR)
					perror("ERROR dup 6");
		}
		if (execve(exec->cmd_path, exec->cmd, envp) == ERROR)
		{
			close (exec->infile);
			ft_free(shell, "ERROR execve");
			exit(1);
		}
	}
	else
	{
		if (waitpid(exec->pid, NULL, 0) == ERROR)
			perror("ERROR waitpid");
	}
	if (lst->prev != NULL && lst->next != NULL)
		close(lst->prev->pipe_fd[0]);
	if (lst->next != NULL)
		close(lst->pipe_fd[1]);
}

void	ft_check_execute(t_shell *shell, char **envp)
{
	t_cmds	*lst;
	int		i;
	t_exec	*exec;

	lst = shell->arg;
	exec = shell->exec;
	if (shell->pipe == 1)
	{
		while (lst)
		{	
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
				if (ft_check_cmd(shell, lst->value_split[i], envp, lst->value_split, i) == FALSE)
					break ;
				if (lst->value_split[i] != NULL)
				i++;
			}
			if (shell->exec->cmd != NULL)
				ft_execute_cmd(shell, shell->exec, envp, lst);
			if (exec->infile > 2)
				close(exec->infile);
			if (exec->outfile > 2)
				close(exec->outfile);
			if (shell->exec != NULL)
				ft_free_exec(shell);
			lst = lst->next;
		}
	}
	else
	{
		while (lst)
		{	
			i = 0;
			if (shell->pipe > 1)
			{
				if (pipe(lst->pipe_fd) == ERROR)
				{
					perror("ERROR pipe");
					break ;
				}
				shell->pipe--;
			}
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
				if (ft_check_cmd(shell, lst->value_split[i], envp, lst->value_split, i) == FALSE)
					break ;
				if (lst->value_split[i] != NULL)
				i++;
			}
			if (shell->exec->cmd != NULL)
				ft_execute_pipe(shell, shell->exec, envp, lst);
			if (exec->infile > 2)
				close(exec->infile);
			if (exec->outfile > 2)
				close(exec->outfile);
			if (shell->exec != NULL)
				ft_free_exec(shell);
			if (lst->next == NULL)
				close(lst->prev->pipe_fd[0]);
			lst = lst->next;
		}
	}
}

void	ft_minishell(t_shell *shell, char **envp)
{
	if (ft_check_error_redirect(shell) == FALSE)
		return ;
	//ft_init_heredoc(shell);
	ft_count_heredoc(shell);
	if (shell->arg->hdoc == TRUE)
		ft_init_heredoc(shell);
	ft_check_execute(shell, envp);
}

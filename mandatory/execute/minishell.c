/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:35:26 by mcloarec          #+#    #+#             */
/*   Updated: 2022/10/21 19:12:45 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			if (ft_valid_redirect(lst->value_split[i]) != 0
				&& (lst->value_split[i + 1] == NULL
					|| ft_valid_redirect(lst->value_split[i + 1]) != 0))
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

int	ft_check_infile(t_exec *exec, t_cmds *lst, int i)
{
	if (i != 0 && ft_valid_redirect(lst->value_split[i - 1]) == 2)
	{
		if (exec->in > 2)
			close(exec->in);
		exec->in = open(lst->value_split[i], O_RDONLY, 0644);
		if (exec->in == -1)
		{
			perror("File error ");
			return (FALSE);
		}
	}
	return (TRUE);
}

int	ft_check_outfile(t_exec *exec, char **tab, int i)
{
	if (i != 0 && ft_valid_redirect(tab[i - 1]) == 3)
	{
		if (exec->out > 2)
			close(exec->out);
		exec->out = open(tab[i], (O_RDWR | O_APPEND | O_CREAT), 0644);
		if (exec->out == -1)
		{
			perror("File error ");
			return (FALSE);
		}
	}
	else if (i != 0 && ft_valid_redirect(tab[i - 1]) == 4)
	{
		if (exec->out > 2)
			close(exec->out);
		exec->out = open(tab[i], (O_RDWR | O_TRUNC | O_CREAT), 0644);
		if (exec->out == -1)
		{
			perror("File error ");
			return (FALSE);
		}
	}
	return (TRUE);
}

int	ft_check_first(t_shell *shell, char **envp, char *s)
{
	if (ft_get_path(shell, s, envp) == -1
		&& ft_valid_redirect(s) == FALSE)
	{
		ft_putendl_fd("First arg must be cmd or redirection", 2);
		return (FALSE);
	}
	return (TRUE);
}

/* int	ft_check_cmd(t_exec *exec, t_cmds *lst, int *i, char **envp) */
/* { */
/* 	(void) envp; */
/* 	if (exec->cmd != NULL) */
/* 	return (TRUE); */
/* } */

void	ft_check_execute(t_shell *shell, char **envp)
{
	t_cmds	*lst;
	int		i;
	t_exec	*exec;

	(void) envp;
	lst = shell->arg;
	exec = shell->exec;
	while (lst)
	{	
		i = 0;
		while (lst->value_split[i])
		{
			if (ft_check_first(shell, envp, lst->value_split[i]) == FALSE
				&& i == 0)
				break ;
			if (ft_check_infile(exec, lst, i) == FALSE)
				break ;
			if (ft_check_outfile(exec, lst->value_split, i) == FALSE)
				break ;
			/* if (ft_check_cmd(exec, lst, &i, envp) == FALSE) */
			/* 	break ; */
			i++;
		}
		//ft_execute_cmd();
		if (exec->in > 2)
			close(exec->in);
		if (exec->out > 2 )
			close(exec->out);
		ft_free_exec(shell);
		lst = lst->next;
	}
}

void	ft_minishell(t_shell *shell, char **envp)
{
//	(void) envp;
	if (ft_check_error_redirect(shell) == FALSE)
		return ;
	ft_init_heredoc(shell);
	ft_check_execute(shell, envp);
}

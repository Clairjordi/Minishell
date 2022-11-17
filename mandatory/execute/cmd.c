/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:25:34 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/17 09:34:29 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_add_opt_arg(t_shell *shell, char **tab, int i)
{
	if (ft_check_q(tab[i][0]) == 1 && ft_is_not_redirection(tab[i]) == TRUE)
		tab[i] = ft_delete_quotes_redirect(shell, tab[i]);
	shell->exec->cmd = ft_realloc_tab_char(shell->exec->cmd, tab[i]);
	if (shell->exec->cmd == NULL)
		ft_free_malloc(shell);
}

int	ft_add_cmd(t_shell *shell, char *s)
{
	if (shell->exec->cmd != NULL
		&& ft_get_path(shell, s) != NULL)
	{
		perror("ERROR cmd ");
		g_minishell.status = 1;
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

int	ft_check_point(t_shell *shell, char **tab, int i)
{	
	if (i == 0 && shell->exec->cmd_path == NULL
		&& ft_valid_redirect(tab[i]) == FALSE)
	{
		if (tab[i][0] == '.' && tab[i][1] == '\0')
		{
			ft_putendl_fd("filename argument required", 2);
			g_minishell.status = 2;
			return (FALSE);
		}
	}
	else if (i > 0 && shell->exec->cmd_path == NULL
		&& ft_valid_redirect(tab[i]) == FALSE
		&& ft_valid_redirect(tab[i - 1]) == FALSE)
	{
		if (tab[i][0] == '.' && tab[i][1] == '\0')
		{
			ft_putendl_fd("filename argument required", 2);
			g_minishell.status = 2;
			return (FALSE);
		}
	}
	return (TRUE);
}

static int	ft_check_cmd_bis(t_shell *shell, char **tab, int i)
{
	if (ft_get_path(shell, tab[i]) == NULL
		|| (tab[i][0] == '.' && tab[i][1] == '.' && tab[i][2] == '\0'))
	{
		if (tab[i][0] == '.' && tab[i][1] == '/')
		{
			ft_putendl_fd("Permission denied", 2);
			g_minishell.status = 126;
		}
		else
		{
			ft_putendl_fd("Command not found", 2);
			g_minishell.status = 127;
		}
		return (FALSE);
	}
	if (tab[i][0] == '\0')
	{
		ft_putendl_fd("Command not found", 2);
		g_minishell.status = 127;
		return (FALSE);
	}
	ft_add_cmd(shell, tab[i]);
	return (TRUE);
}

int	ft_check_cmd(t_shell *shell, char **tab, int i)
{
	if (ft_check_point(shell, tab, i) == FALSE)
		return (FALSE);
	if (i == 0 && shell->exec->cmd_path == NULL
		&& ft_valid_redirect(tab[i]) == FALSE)
	{
		if (ft_check_cmd_bis(shell, tab, i) == FALSE)
			return (FALSE);
	}
	else if (i > 0 && shell->exec->cmd_path == NULL
		&& ft_valid_redirect(tab[i]) == FALSE
		&& ft_valid_redirect(tab[i - 1]) == FALSE)
	{
		if (ft_check_cmd_bis(shell, tab, i) == FALSE)
			return (FALSE);
	}
	else if (i > 0 && shell->exec->cmd != NULL
		&& ft_valid_redirect(tab[i]) == FALSE
		&& ft_valid_redirect(tab[i - 1]) == FALSE)
		ft_add_opt_arg(shell, tab, i);
	return (TRUE);
}

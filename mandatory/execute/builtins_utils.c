/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:03:07 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/17 15:56:56 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_check_is_builtins_bis(t_shell *shell, char **tab, int *i)
{
	if (ft_strcmp(tab[*i], "cd") == 0)
	{
		ft_create_builtins_tab(shell, tab, i);
		return (TRUE);
	}
	else if (ft_strcmp(tab[*i], "export") == 0)
	{
		ft_create_builtins_tab(shell, tab, i);
		return (TRUE);
	}
	else if (ft_strcmp(tab[*i], "unset") == 0)
	{
		ft_create_builtins_tab(shell, tab, i);
		return (TRUE);
	}
	else if (ft_strcmp(tab[*i], "exit") == 0)
	{
		ft_create_builtins_tab(shell, tab, i);
		return (TRUE);
	}
	return (0);
}

int	ft_check_is_builtins(t_shell *shell, char **tab, int *i)
{
	if (ft_check_is_builtins_bis(shell, tab, i) == TRUE)
		return (TRUE);
	if (ft_strcmp(tab[*i], "pwd") == 0)
	{
		ft_create_builtins_tab(shell, tab, i);
		return (TRUE);
	}
	else if (ft_strcmp(tab[*i], "env") == 0)
	{
		ft_create_builtins_tab(shell, tab, i);
		return (TRUE);
	}
	else if (ft_strcmp(tab[*i], "echo") == 0)
	{
		ft_create_builtins_tab(shell, tab, i);
		return (TRUE);
	}
	return (FALSE);
}

int	ft_verif_opt_builtins(t_shell *shell)
{
	if (ft_strcmp(shell->exec->builtins[0], "pwd") == 0
		|| ft_strcmp(shell->exec->builtins[0], "cd") == 0
		|| ft_strcmp(shell->exec->builtins[0], "export") == 0
		|| ft_strcmp(shell->exec->builtins[0], "unset") == 0)
	{
		if (shell->exec->builtins[1] != NULL
			&& shell->exec->builtins[1][0] == '-')
		{
			ft_putendl_fd("bash : invalid option ", 2);
			g_minishell.status = 2;
			return (FALSE);
		}
	}
	if (ft_strcmp(shell->exec->builtins[0], "env") == 0)
	{
		if (shell->exec->builtins[1] != NULL
			&& shell->exec->builtins[1][0] == '-')
		{
			ft_putendl_fd("bash : invalid option ", 2);
			g_minishell.status = 125;
			return (FALSE);
		}
	}
	return (TRUE);
}

static int	ft_verif_opt_builtins_without_fork(t_shell *shell)
{
	if (ft_strcmp(shell->exec->builtins[0], "cd") == 0
		|| ft_strcmp(shell->exec->builtins[0], "export") == 0
		|| ft_strcmp(shell->exec->builtins[0], "unset") == 0)
	{
		if (shell->exec->builtins[1] != NULL
			&& shell->exec->builtins[1][0] == '-')
		{
			ft_putendl_fd("bash : invalid option ", 2);
			g_minishell.status = 2;
			return (FALSE);
		}
	}
	return (TRUE);
}

int	ft_check_builtins_without_fork(t_shell *shell)
{	
	if (ft_verif_opt_builtins_without_fork(shell) == FALSE)
		return (TRUE);
	if (ft_strcmp(shell->exec->builtins[0], "export") == 0)
	{
		ft_export(shell);
		return (TRUE);
	}	
	if (ft_strcmp(shell->exec->builtins[0], "exit") == 0)
	{
		ft_exit(shell, shell->exec->builtins);
		return (TRUE);
	}
	if (ft_strcmp(shell->exec->builtins[0], "cd") == 0)
	{
		ft_cd(shell, shell->exec->builtins);
		return (TRUE);
	}
	if (ft_strcmp(shell->exec->builtins[0], "unset") == 0)
	{
		ft_unset(shell);
		return (TRUE);
	}
	return (FALSE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 16:56:53 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/17 16:16:18 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_create_builtins_tab_append(t_shell *shell, char **tab, int i)
{
	if (ft_valid_redirect(tab[i]) == 4)
	{
		if (shell->exec->outfile > 2)
			close(shell->exec->outfile);
		if (ft_check_q(tab[i][0]) == 1 && ft_is_not_redirection(tab[i]) == 0)
			tab[i] = ft_delete_quotes_redirect(shell, tab[i]);
		shell->exec->outfile = open(tab[i + 1],
				(O_RDWR | O_TRUNC | O_CREAT), 0644);
		if (shell->exec->outfile == -1)
		{
			perror("File error ");
			g_minishell.status = 1;
			return (FALSE);
		}
	}
	return (TRUE);
}

static int	ft_create_builtins_tab_outfile(t_shell *shell, char **tab, int i)
{
	if (ft_valid_redirect(tab[i]) == 3)
	{
		if (shell->exec->outfile > 2)
			close(shell->exec->outfile);
		if (ft_check_q(tab[i][0]) == 1 && ft_is_not_redirection(tab[i]) == TRUE)
			tab[i] = ft_delete_quotes_redirect(shell, tab[i]);
		shell->exec->outfile = open(tab[i + 1],
				(O_RDWR | O_APPEND | O_CREAT), 0644);
		if (shell->exec->outfile == -1)
		{
			perror("File error ");
			g_minishell.status = 1;
			return (FALSE);
		}
	}
	return (TRUE);
}

static int	ft_create_builtins_tab_infile(t_shell *shell, char **tab, int i)
{
	if (shell->exec->infile > 2)
		close(shell->exec->infile);
	shell->exec->infile = open(tab[i + 1], O_RDONLY, 0644);
	if (shell->exec->infile == -1)
	{
		perror("File error ");
		g_minishell.status = 1;
		return (FALSE);
	}
	return (TRUE);
}

void	ft_create_builtins_tab(t_shell *shell, char **tab, int *i)
{
	while (tab[*i])
	{
		if (shell->exec->builtins == NULL
			&& ft_valid_redirect(tab[*i]) == FALSE)
			ft_add_builtins(shell, tab[*i]);
		else if (shell->exec->builtins != NULL
			&& ft_valid_redirect(tab[*i]) == FALSE
			&& ft_valid_redirect(tab[*i - 1]) == FALSE)
			ft_add_opt_arg_builtins(shell, tab, (*i));
		else if (ft_valid_redirect(tab[*i]) == 2)
		{
			if (ft_create_builtins_tab_infile(shell, tab, (*i)) == FALSE)
				return ;
		}
		if (ft_create_builtins_tab_append(shell, tab, (*i)) == FALSE)
			return ;
		if (ft_create_builtins_tab_outfile(shell, tab, (*i)) == FALSE)
			return ;
		(*i)++;
	}
}

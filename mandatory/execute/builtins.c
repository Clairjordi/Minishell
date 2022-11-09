/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 16:56:53 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/05 18:59:47 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_add_opt_arg_builtins(t_shell *shell, char **tab, int i)
{
	if (ft_check_q(tab[i][0]) == 1 && ft_is_not_redirection(tab[i]) == TRUE)
		tab[i] = ft_delete_quotes_redirect(shell, tab[i]);
	shell->exec->builtins = ft_realloc_tab_char(shell->exec->builtins, tab[i]);
	if (shell->exec->builtins == NULL)
		ft_free_malloc(shell);
}

void	ft_add_builtins(t_shell *shell, char **tab, int i)
{
	if (shell->exec->builtins == NULL)
	{
		shell->exec->builtins = ft_calloc(sizeof(char *), 2);
		if (!shell->exec->builtins)
			ft_free_malloc(shell);
		shell->exec->builtins[0] = ft_strdup(tab[i]);
		if (shell->exec->builtins[0] == NULL)
			ft_free_malloc(shell);
		shell->exec->builtins[1] = NULL;
	}
}

void	ft_create_builtins_tab_bis(t_shell *shell, char **tab, int **i)
{
	if (ft_valid_redirect(tab[**i]) == 4)
	{
		if (shell->exec->outfile > 2)
			close(shell->exec->outfile);
		if (ft_check_q(tab[**i][0]) == 1 && ft_is_not_redirection(tab[**i]) == 0)
			tab[**i] = ft_delete_quotes_redirect(shell, tab[**i]);
		shell->exec->outfile = open(tab[**i + 1], (O_RDWR | O_TRUNC | O_CREAT), 0644);
		if (shell->exec->outfile == -1)
		{
			perror("File error");
			g_g.status = 1;
		}
	}
	else if (ft_valid_redirect(tab[**i]) == 3)
	{
		if (shell->exec->outfile > 2)
			close(shell->exec->outfile);
		if (ft_check_q(tab[**i][0]) == 1 && ft_is_not_redirection(tab[**i]) == TRUE)
			tab[**i] = ft_delete_quotes_redirect(shell, tab[**i]);
		shell->exec->outfile = open(tab[**i + 1], (O_RDWR | O_APPEND | O_CREAT), 0644);
		if (shell->exec->outfile == -1)
		{
			perror("File error");
			g_g.status = 1;
		}
	}
}

void	ft_create_builtins_tab(t_shell *shell, char **tab, int **i)
{
	while (tab[**i])
	{
		if (shell->exec->builtins == NULL && ft_valid_redirect(tab[**i]) == FALSE)
			ft_add_builtins(shell, tab, **i);
		else if (shell->exec->builtins != NULL && ft_valid_redirect(tab[**i]) == FALSE
			&& ft_valid_redirect(tab[**i - 1]) == FALSE)
			ft_add_opt_arg_builtins(shell, tab, **i);
		else if (ft_valid_redirect(tab[**i]) == 2)
		{
			if (shell->exec->infile > 2)
				close(shell->exec->infile);
			shell->exec->infile = open(tab[**i + 1], O_RDONLY, 0644);
			if (shell->exec->infile == -1)
			{
				perror("File error");
				g_g.status = 1;
			}
		}
		ft_create_builtins_tab_bis(shell, tab, i);
		(**i)++;
	}
}

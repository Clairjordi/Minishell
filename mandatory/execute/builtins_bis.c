/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:09:07 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/17 16:09:30 by clorcery         ###   ########.fr       */
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

void	ft_add_builtins(t_shell *shell, char *cmd_built)
{
	if (shell->exec->builtins == NULL)
	{
		shell->exec->builtins = ft_calloc(sizeof(char *), 2);
		if (!shell->exec->builtins)
			ft_free_malloc(shell);
		shell->exec->builtins[0] = ft_strdup(cmd_built);
		if (shell->exec->builtins[0] == NULL)
			ft_free_malloc(shell);
		shell->exec->builtins[1] = NULL;
	}
}

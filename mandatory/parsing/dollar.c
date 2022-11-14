/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:39:51 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/11 15:13:10 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_rep_if_dollar_join(t_shell *shell, int i, int *j, t_cmds *lst)
{
	char	*variable;

	variable = NULL;
	while (lst->value_split[i][*j])
	{		
		if (!(lst->value_split[i][*j] == '\"' && shell->quote != 1))
		{
			variable = ft_charjoin(variable, lst->value_split[i][*j]);
			if (variable == NULL)
				ft_free_malloc(shell);
		}
		if (ft_isalnum(lst->value_split[i][*j + 1]) == 0
				&& lst->value_split[i][*j + 1] != '_')
			break ;
		(*j)++;
	}
	return (variable);
}

static char	*ft_rep_if_dollar_bis(t_shell *shell, int i, int *j, t_cmds *lst)
{
	char	*tmp;
	char	*var;

	var = NULL;
	tmp = NULL;
	tmp = ft_rep_if_dollar_join(shell, i, j, lst);
	if (ft_getenv(shell, tmp) == NULL)
	{
		free(tmp);
		if (shell->tmp != NULL)
			return (shell->tmp);
		var = ft_cdup('\0');
		if (var == NULL)
			ft_free_malloc(shell);
		return (var);
	}
	var = ft_strdup(ft_getenv(shell, tmp));
	free(tmp);
	if (shell->tmp != NULL)
		var = ft_strjoin_free(shell->tmp, var, 3);
	if (var == NULL)
		ft_free_malloc(shell);
	return (var);
}

static void	ft_rep_if_dollar_num(t_shell *shell, int i, int *j, t_cmds *lst)
{
	(*j) = (*j) + 2;
	while (lst->value_split[i][*j])
	{
		if (shell->dollar == 2 && ft_check_q(lst->value_split[i][*j]) == 1)
			break ;
		shell->tmp = ft_charjoin(shell->tmp, lst->value_split[i][*j]);
		if (shell->tmp == NULL)
			ft_free_malloc(shell);
		(*j)++;
	}
}

static char	*ft_rep_if_interrogation(t_shell *shell, int i, int *j, t_cmds *lst)
{
	char	*status;

	status = NULL;
	if (lst->value_split[i][*j + 1] == '?')
	{
		status = ft_itoa(g_minishell.status);
		if (status == NULL)
			ft_free_malloc(shell);
		(*j)++;
	}
	return (status);
}

char	*ft_rep_if_dollar(t_shell *shell, int i, int *j, t_cmds *lst)
{
	char	*result;

	result = NULL;
	result = ft_rep_if_interrogation(shell, i, j, lst);
	if (result)
		return (result);
	if (ft_isalpha(lst->value_split[i][*j + 1]) == 1
			|| lst->value_split[i][*j + 1] == '_')
	{
		(*j)++;
		result = ft_rep_if_dollar_bis(shell, i, j, lst);
		return (result);
	}
	else if (ft_isdigit(lst->value_split[i][*j + 1]) == 1)
		ft_rep_if_dollar_num(shell, i, j, lst);
	else
	{
		while (lst->value_split[i][++*j])
		{
			shell->tmp = ft_charjoin(shell->tmp, lst->value_split[i][*j]);
			if (shell->tmp == NULL)
				ft_free_malloc(shell);
		}
	}
	return (shell->tmp);
}

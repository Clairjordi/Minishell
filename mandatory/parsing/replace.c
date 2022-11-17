/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:54:59 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/17 16:36:19 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_rep_bis(t_shell *shell, int i, int *j, t_cmds *lst)
{
	char	*new;
	int		redir;

	new = NULL;
	redir = ft_check_redir(lst->value_split[i]);
	if (ft_check_q(lst->value_split[i][*j]) == 1 && redir != 0)
	{
		new = ft_charjoin(shell->tmp, lst->value_split[i][*j]);
		if (new == NULL)
			ft_free_malloc(shell);
		return (new);
	}
	else if (((*j == 0 && ft_check_q(lst->value_split[i][*j]) == 1)
		|| (*j > 0 && ft_check_q(lst->value_split[i][*j]) == 1
		&& lst->value_split[i][*j - 1] == '$'))
			&& ft_check_q(lst->value_split[i][*j + 1]) == 1)
	{
		new = ft_rep_quotes_space(i, j, lst);
		if (new)
		{
			(*j)++;
			return (new);
		}
	}
	return (new);
}

char	*ft_rep(t_shell *shell, int i, int *j, t_cmds *lst)
{
	char	*new;

	new = ft_rep_bis(shell, i, j, lst);
	if (new)
		return (new);
	new = shell->tmp;
	shell->quote = ft_open_quote(shell, lst->value_split[i][*j]);
	if (!(lst->value_split[i][*j] == '\'' && shell->quote != 2)
			&& !(lst->value_split[i][*j] == '\"' && shell->quote != 1))
	{
		new = ft_charjoin(shell->tmp, lst->value_split[i][*j]);
		if (new == NULL)
			ft_free_malloc(shell);
	}
	return (new);
}

void	ft_replace_value_split(t_shell *shell, int *i, t_cmds *lst)
{
	if (shell->tmp != NULL)
	{
		if (lst->value_split[*i][0] == '$'
			&& ft_check_q(lst->value_split[*i][1]) != 1)
			ft_verif_space_value(shell, i, lst);
		else
		{
			lst->value_split[*i] = ft_free_ptr(lst->value_split[*i]);
			lst->value_split[*i] = shell->tmp;
		}
	}
	if (shell->tmp == NULL)
	{
		lst->value_split[*i] = ft_free_ptr(lst->value_split[*i]);
		lst->value_split[*i] = ft_cdup('\0');
	}
}

static void	ft_replace_value_bis(t_shell *shell, int i, int *j, t_cmds *lst)
{
	if (lst->value_split[i][*j] == '$' && shell->dollar != 0)
		shell->tmp = ft_rep_if_dollar(shell, i, j, lst);
	else
	{
		if (lst->value_split[i][*j] == '$' && shell->dollar == 0
			&& ft_check_q(lst->value_split[i][*j + 1]) == 1
			&& shell->quote == 0)
			(*j)++;
		shell->tmp = ft_rep(shell, i, j, lst);
	}
	if (lst->value_split[i][*j] != '\0')
		(*j)++;
	if (shell->quote != 1)
		shell->dollar = ft_check_dollar(lst->value_split[i], *j);
}

void	ft_replace_value(t_shell *shell)
{
	int		i;
	int		j;
	t_cmds	*lst;

	lst = shell->arg;
	while (lst != NULL)
	{
		i = 0;
		while (lst->value_split[i] != NULL)
		{
			shell->tmp = NULL;
			j = 0;
			shell->dollar = ft_check_dollar(lst->value_split[i], j);
			while (lst->value_split[i][j])
				ft_replace_value_bis(shell, i, &j, lst);
			ft_replace_value_split(shell, &i, lst);
			i++;
		}
		lst = lst->next;
	}
	shell->tmp = NULL;
}

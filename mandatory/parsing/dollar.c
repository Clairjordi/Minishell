/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:39:51 by mcloarec          #+#    #+#             */
/*   Updated: 2022/10/12 19:07:11 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_check_dollar(char c)
{
	if (c == '$')
		return (1);
	return (0);
}

char	*ft_rep_if_dollar(t_shell *shell, int i, int *j, t_cmds *lst)
{
	char *var;
	char *tmp;

	var = NULL;
	tmp = NULL;
	/* if (lst->value_split[i][j + 1] == '?') */
	/* 	le truc avec le code erreur bash */
	if (ft_isalpha(lst->value_split[i][*j + 1]) == 1 || lst->value_split[i][*j + 1] == '_')
	{
		(*j)++;
		while (lst->value_split[i][*j])
		{	
			tmp = ft_charjoin(tmp, lst->value_split[i][*j]);
			if (ft_isalnum(lst->value_split[i][*j + 1]) == 0)
			{
				shell->dollar = 0;
				break;
			}
			(*j)++;
		}
		var = ft_strdup(getenv(tmp));
		free(tmp);
		if (shell->tmp != NULL)
			var = ft_strjoin_free(shell->tmp, var, 3);
		shell->dollar = 0;
		return (var);
	}
	else if (ft_isdigit(lst->value_split[i][*j + 1]) == 1)
	{
		(*j) = (*j) + 2;
		while (lst->value_split[i][*j])
		{
			shell->tmp = ft_charjoin(shell->tmp, lst->value_split[i][*j]);
			(*j)++;
		}
	}
	else
	{
		while (lst->value_split[i][*j])
		{
			shell->tmp = ft_charjoin(shell->tmp, lst->value_split[i][*j]);
			(*j)++;
		}
	}
	shell->dollar = 0;
	return (shell->tmp);
}

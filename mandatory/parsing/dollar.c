/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:39:51 by mcloarec          #+#    #+#             */
/*   Updated: 2022/10/13 18:32:56 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_check_dollar(t_shell *shell, char *s)
{
	int	i;

	i = 0;
	(void) shell;
	while (s[i])
	{
		if (s[0] == '\'' || (ft_sep(s[i]) == 4 && s[i - 1] != '\"') /* || (s[i] == '$' && */ )
			return (0);
		if (s[i] == '$' && (ft_isalpha(s[i + 1]) == 1 || s[i + 1] == '_'))
			return (1);
		if (s[i] == '$' && ft_isdigit(s[i + 1]) == 1)
			return (2);
		//if ((ft_sep(s[i]) == 4 && s[i - 1] == '\"')	
		i++;
	}
	return (0);
}

char	*ft_rep_if_dollar(t_shell *shell, int i, int *j, t_cmds *lst)
{
	char *var;
	char *tmp;

	var = NULL;
	tmp = NULL;
	shell->test = -1;
	/* if (lst->value_split[i][j + 1] == '?') */
	/* 	le truc avec le code erreur bash */
	while (lst->value_split[i][*j] != '$')
		(*j)++;
	if (ft_isalpha(lst->value_split[i][*j + 1]) == 1 || lst->value_split[i][*j + 1] == '_')
	{
		(*j)++;
		while (lst->value_split[i][*j])
		{		
			if (!(lst->value_split[i][*j] == '\"' && shell->quote != 1))
				tmp = ft_charjoin(tmp, lst->value_split[i][*j]);
			if (ft_isalnum(lst->value_split[i][*j + 1]) == 0)
				break;
			(*j)++;
		}
		if (getenv(tmp) == NULL)
		{
			if (shell->tmp != NULL)
			{
				free(tmp);
				return (shell->tmp);
			}
			free(tmp);
			shell->test++;
			return (var);
		}
		var = ft_strdup(getenv(tmp));
		if (var == NULL)
		{
			free(tmp);
			ft_free_malloc(shell);
		}
		free(tmp);
		if (shell->tmp != NULL)
			var = ft_strjoin_free(shell->tmp, var, 3);
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
	return (shell->tmp);
}

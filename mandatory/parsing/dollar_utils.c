/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:23:28 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/14 18:02:23 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(t_shell *shell, char *name)
{
	char		*value;
	t_envcpy	*lst;

	value = NULL;
	lst = ft_check_name_envcpy(shell->env->first, name);
	if (lst != NULL)
	{
		value = lst->value;
		return (value);
	}
	return (NULL);
}

int	ft_check_dollar(char *s, int i)
{
	while (s[i])
	{
		if (s[i] == '\'' && s[i + 1] == '\'')
			i++;
		if (s[i] == '\"' && s[i + 1] == '\"')
			i++;
		if ((s[0] == '\'' && i == 0)
			|| (ft_sep(s[i]) == 4 && s[i - 1] != '\"'))
			return (0);
		if (i > 1 && ft_sep(s[i]) == 4 && s[i - 1] == '\"' && s[i - 2] == '\"')
			return (0);
		else if (s[i] == '$' && ft_check_q(s[i + 1]) == 1)
			return (0);
		else if (s[i] == '$' && (ft_isalpha(s[i + 1]) == 1 || s[i + 1] == '_'))
			return (1);
		else if (s[i] == '$' && ft_isdigit(s[i + 1]) == 1)
			return (2);
		else if (s[i] == '$' && s[i + 1] == '?')
			return (3);
		i++;
	}
	return (0);
}

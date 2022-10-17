/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:23:28 by clorcery          #+#    #+#             */
/*   Updated: 2022/10/17 11:50:17 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_dollar(char *s, int i)
{
	while (s[i])
	{
		if (s[i] == '\'' && s[i + 1] == '\'')
			i++;
		if ((s[0] == '\'' && i == 0)
			|| (ft_sep(s[i]) == 4 && s[i - 1] != '\"'))
			return (0);
		else if (s[i] == '$' && ft_check_q(s[i + 1]) == 1)
			return (0);
		else if (s[i] == '$' && (ft_isalpha(s[i + 1]) == 1 || s[i + 1] == '_'))
			return (1);
		else if (s[i] == '$' && ft_isdigit(s[i + 1]) == 1)
			return (2);
		else if (s[i] == '$' && s[i + 1] == '?')
			return (3);
		else if ((s[0] == '\'' && i == 0)
			|| (ft_sep(s[i]) == 4 && s[i - 1] != '\"'))
			return (0);
		i++;
	}
	return (0);
}

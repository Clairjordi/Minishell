/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:07:17 by clorcery          #+#    #+#             */
/*   Updated: 2022/10/07 17:34:41 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_q(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	ft_sep(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	else if (c == '\"')
		return (2);
	else if (c == '\'')
		return (4);
	else if (c == '<' || c == '>')
		return (3);
	return (0);
}

int	ft_len_va(char *var, int start, char c)
{
	int	i;

	i = start;
	while (var[i])
	{
		if (var[i] == c)
		{
			i++;
			return (i);
		}
		i++;
	}
	if (var[i] == '\0')
		i++;
	return (i);
}

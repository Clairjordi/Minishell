/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:07:17 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/17 17:10:48 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_close_std(void)
{
	close(0);
	close(1);
}

int	ft_size_lst(t_cmds *lst)
{
	int	size;

	size = 0;
	if (lst == NULL)
		return (0);
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

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

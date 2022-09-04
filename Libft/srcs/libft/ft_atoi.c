/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:28:16 by clorcery          #+#    #+#             */
/*   Updated: 2022/03/30 18:37:53 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

int	ft_atoi(const char *nptr)
{
	int				i;
	unsigned int	reponse;
	int				nb;

	i = 0;
	reponse = 0;
	nb = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
		{
			nb *= -1;
		}
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		reponse = reponse * 10;
		reponse = reponse + nptr[i] - '0';
		i++;
	}
	return (reponse * nb);
}

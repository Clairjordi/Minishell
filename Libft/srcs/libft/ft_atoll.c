/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:28:16 by clorcery          #+#    #+#             */
/*   Updated: 2022/07/09 14:32:01 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

long long	ft_atoll(const char *nptr)
{
	long long			i;
	unsigned long int	reponse;
	int					nb;

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

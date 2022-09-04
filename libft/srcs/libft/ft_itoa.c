/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:30:25 by clorcery          #+#    #+#             */
/*   Updated: 2022/04/04 16:17:50 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

static int	count_size(int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*tab;
	int		len;
	long	nb;

	nb = n;
	len = count_size(n);
	tab = malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (NULL);
	tab[len--] = '\0';
	if (n < 0)
	{
		tab[0] = '-';
		nb *= -1;
	}
	while (nb > 9)
	{
		tab[len] = (nb % 10) + '0';
		nb = nb / 10;
		len--;
	}
	tab[len] = nb + '0';
	return (tab);
}

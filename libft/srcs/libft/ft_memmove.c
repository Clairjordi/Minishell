/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:35:14 by clorcery          #+#    #+#             */
/*   Updated: 2022/03/30 17:42:26 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dst;
	const char	*sc;
	char		*enddst;
	const char	*endsc;

	dst = dest;
	sc = src;
	if (dest == 0 && src == 0)
		return (dest);
	enddst = dst + (n - 1);
	endsc = sc + (n - 1);
	if (sc > dst)
	{
		while (n--)
			*dst++ = *sc++;
	}
	else
		while (n--)
			*enddst-- = *endsc--;
	return (dest);
}

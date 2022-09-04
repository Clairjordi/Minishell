/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:35:00 by clorcery          #+#    #+#             */
/*   Updated: 2022/03/30 17:41:45 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*cpydest;
	const char	*cpysrc;

	cpydest = dest;
	cpysrc = src;
	if (dest == NULL && src == NULL)
		return (dest);
	while (n > 0)
	{
		*cpydest++ = *cpysrc++;
		n--;
	}
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:34:27 by clorcery          #+#    #+#             */
/*   Updated: 2022/04/05 17:56:14 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	ch;

	p = (unsigned char *)s;
	ch = (unsigned char) c;
	while (n > 0)
	{
		if (*p == ch)
			return ((char *) p);
		p++;
		n--;
	}
	return (NULL);
}

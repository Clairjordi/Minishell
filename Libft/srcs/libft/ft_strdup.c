/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:09:53 by clorcery          #+#    #+#             */
/*   Updated: 2022/03/31 11:30:51 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		len;

	len = ft_strlen(s);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s, (len + 1));
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:05:45 by clorcery          #+#    #+#             */
/*   Updated: 2022/08/25 15:06:16 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

char	*ft_join_loop(char const *s1, char const *s2)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	if (!s1)
		dest = malloc(sizeof(char) * (ft_strlen(s2) + 1));
	else
		dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		dest[i++] = s2[j++];
	if (s1)
		free((char *)s1);
	dest[i] = '\0';
	return (dest);
}

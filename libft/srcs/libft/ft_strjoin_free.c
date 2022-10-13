/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:05:45 by clorcery          #+#    #+#             */
/*   Updated: 2022/10/13 14:20:20 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

static char	*ft_alloc_mem(char *dest, char *s1, char *s2)
{
	if (!s1)
		dest = malloc(sizeof(char) * (ft_strlen(s2) + 1));
	else if (!s2)
		dest = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	else
		dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	return (dest);
}

static void	ft_free_join(char *s1, char *s2, int f)
{
	if (f == 1)
		free((char *)s1);
	if (f == 2)
		free((char *)s2);
	if (f == 3)
	{
		free((char *)s1);
		free((char *)s2);
	}
}

char	*ft_strjoin_free(char const *s1, char const *s2, int f)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	dest = NULL;
	dest = ft_alloc_mem(dest, (char *)s1, (char *)s2);
	if (dest == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		dest[i++] = s2[j++];
	ft_free_join((char *)s1, (char *)s2, f);
	dest[i] = '\0';
	return (dest);
}

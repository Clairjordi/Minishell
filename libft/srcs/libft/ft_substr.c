/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:05:35 by clorcery          #+#    #+#             */
/*   Updated: 2022/04/11 16:01:11 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (ft_strlen(s) < start)
	{
		str = malloc(sizeof(char));
		str[0] = '\0';
		return (str);
	}
	else if (ft_strlen(s + start) < len)
		str = malloc(sizeof(char) * (ft_strlen(s + start) + 1));
	else
		str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (s[i] && i < len && start < ft_strlen(s))
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

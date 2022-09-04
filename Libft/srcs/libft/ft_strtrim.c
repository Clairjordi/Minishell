/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:57:51 by clorcery          #+#    #+#             */
/*   Updated: 2022/04/11 15:32:01 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (ft_strchr(set, s1[i]) != NULL)
		i++;
	j = ft_strlen(s1);
	while (ft_strchr(set, s1[j - 1]) != NULL)
		j--;
	return (ft_substr(s1, i, (j - i)));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:07:17 by clorcery          #+#    #+#             */
/*   Updated: 2022/04/12 09:53:17 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;

	if (nmemb > 2147483647 || size > 2147483647)
		return (NULL);
	array = malloc(nmemb * size);
	if (!array || (size * nmemb) > 2147483647)
		return (NULL);
	ft_bzero(array, size * nmemb);
	return (array);
}

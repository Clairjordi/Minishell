/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstlast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:27:28 by clorcery          #+#    #+#             */
/*   Updated: 2022/07/19 10:30:14 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

t_dlist	*ft_dlstlast(t_dlist *lst)
{
	t_dlist	*tmp;

	tmp = lst;
	if (lst == NULL)
		return (NULL);
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

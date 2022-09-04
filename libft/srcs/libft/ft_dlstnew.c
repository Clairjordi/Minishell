/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:13:48 by clorcery          #+#    #+#             */
/*   Updated: 2022/07/11 17:41:07 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

t_dlist	*ft_dlstnew(int value)
{
	t_dlist	*new_dlst;

	new_dlst = malloc(sizeof(t_dlist));
	if (!new_dlst)
		return (NULL);
	new_dlst->data = value;
	new_dlst->prev = NULL;
	new_dlst->next = NULL;
	return (new_dlst);
}

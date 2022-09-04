/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:36:57 by clorcery          #+#    #+#             */
/*   Updated: 2022/07/14 18:46:01 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

void	ft_dlstadd_back(t_dlist **list, t_dlist *new)
{
	t_dlist	*lst;

	lst = *list;
	while (lst->next)
		lst = lst->next;
	new->prev = lst;
	new->next = NULL;
	lst->next = new;
}

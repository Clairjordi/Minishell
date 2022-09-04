/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:00:47 by clorcery          #+#    #+#             */
/*   Updated: 2022/04/11 16:00:18 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*buf;

	tmp = *lst;
	if (*lst == NULL)
		return ;
	while (tmp != NULL)
	{
		buf = tmp->next;
		ft_lstdelone(tmp, del);
		tmp = buf;
	}
	*lst = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:52:45 by clorcery          #+#    #+#             */
/*   Updated: 2022/04/12 09:52:37 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_elem;
	t_list	*tmp;
	t_list	*start;

	if (lst == NULL)
		return (NULL);
	tmp = lst;
	start = ft_lstnew((*f)(lst->content));
	if (start == NULL)
		return (NULL);
	tmp = tmp->next;
	while (tmp != NULL)
	{
		new_elem = ft_lstnew((*f)(tmp->content));
		if (new_elem == NULL)
		{
			ft_lstclear(&tmp, del);
			return (NULL);
		}
		ft_lstadd_back(&start, new_elem);
		tmp = tmp->next;
	}
	new_elem = NULL;
	return (start);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:17:00 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/21 11:21:57 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmds	*ft_lstnew_cmd(char *s)
{
	t_cmds	*new_dlst;

	new_dlst = malloc(sizeof(t_cmds));
	if (!new_dlst)
		return (NULL);
	new_dlst->cmd = s;
	new_dlst->prev = NULL;
	new_dlst->next = NULL;
	return (new_dlst);
}

void	ft_lstaddback_cmd(t_cmds **list, t_cmds *new_elem)
{
	t_cmds	*lst;

	lst = *list;
	while (lst->next)
		lst = lst->next;
	new_elem->prev = lst;
	new_elem->next = NULL;
	lst->next = new_elem;
}

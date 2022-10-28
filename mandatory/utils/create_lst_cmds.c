/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:17:00 by clorcery          #+#    #+#             */
/*   Updated: 2022/10/28 14:06:22 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmds	*ft_lstnew_cmd(char *s, t_shell *shell)
{
	t_cmds	*new_dlst;

	new_dlst = malloc(sizeof(t_cmds));
	if (!new_dlst)
		return (NULL);
	ft_init_cmds(new_dlst);
	if (s != NULL)
		new_dlst->value = ft_strdup(s);
	if (new_dlst->value == NULL)
		ft_free_malloc(shell);
	new_dlst->value_split = ft_split_value(new_dlst->value, ' ');
	if (new_dlst->value_split == NULL)
		ft_free_malloc(shell);
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

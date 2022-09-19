/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:01:37 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/19 18:44:46 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_parsing(char *s, t_shell *shell, t_cmds *cmds)
{
	int	i;
	int	j;
	t_cmds new_elem;
	char	**tab_cmd;

	i = 0;
	j = 1;
	tab_cmd = ft_split(s, '|');
	if (!tab_cmd)
		ft_free_malloc(shell);
	//A SUPPR
	while (tab_cmd[i] != NULL)
	{
		while (tab_cmd[i][j])
		{
			
			j++;
		}
		i++;
	}
		ft_printf("%s\n", tab_cmd[i++]);
	ft_free_tab_char(tab_cmd);
	//
	cmds = ft_lstnew_cmd(tab_cmd[0]);
	while (tab_cmd[j]!= NULL)
	{
		new_elem = ft_lstnew_cmd(tab_cmd[j]);
		ft_lstaddback_cmd(&cmds, new_elem);
		j++;
	}

}

t_cmds	*ft_lstnew_cmd()
{
	t_cmds	*new_dlst;

	new_dlst = malloc(sizeof(t_dlist));
	if (!new_dlst)
		return (NULL);
	new_dlst->data = value;
	new_dlst->prev = NULL;
	new_dlst->next = NULL;
	return (new_dlst);
}

void	ft_lstaddback_cmd(t_cmds **list, t_cmds *new)
{
	t_cmds	*lst;

	lst = *list;
	while (lst->next)
		lst = lst->next;
	new->prev = lst;
	new->next = NULL;
	lst->next = new;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:30:28 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/17 09:35:20 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_get_idx_heredoc(t_cmds *lst)
{
	int		i;

	i = lst->idx_hdoc;
	while (lst->value_split[i] != NULL)
	{
		if (ft_strcmp(lst->value_split[i], "<<") == 0)
		{
			lst->idx_hdoc = i + 1;
			break ;
		}
		i++;
	}
}

void	ft_count_heredoc(t_shell *shell)
{
	int		i;
	t_cmds	*lst;

	lst = shell->arg;
	while (lst)
	{
		i = 0;
		while (lst->value_split[i] != NULL)
		{
			if (ft_strcmp(lst->value_split[i], "<<") == 0)
				lst->count_hdoc++;
			i++;
		}
		if (lst->count_hdoc != 0)
			lst->hdoc = TRUE;
		lst = lst->next;
	}
}

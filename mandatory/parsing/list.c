/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:45:51 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/28 15:53:03 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_create_lst(t_shell *shell)
{
	int		i;
	t_cmds	*new;

	i = 1;
	shell->arg = ft_lstnew_cmd(shell->tab_cmd[0]);
	while (shell->tab_cmd[i] != NULL)
	{
		new = ft_lstnew_cmd(shell->tab_cmd[i]);
		ft_lstaddback_cmd(&shell->arg, new);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:52:55 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/16 18:57:45 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_verif_malloc(t_shell *shell, char *s)
{
	if (s == NULL)
		ft_free_malloc(shell);
}

t_envcpy	*ft_check_name_envcpy(t_envcpy *lst, char *s)
{
	t_envcpy	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, s) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:57:11 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/09 16:40:29 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(char **tab)
{
	if (tab[2] != NULL)
	{
		ft_putendl_fd("bash: cd: too many arguments", 2);
		g_g.status = 1;
	}
	if (chdir(tab[1]) == -1)
	{
		perror("chdir");
		g_g.status = 1;
	}
	g_g.status = 0;
}

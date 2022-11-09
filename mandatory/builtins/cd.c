/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:57:11 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/09 19:26:48 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(char **tab)
{
	if (tab[1] == NULL)
	{
		ft_putendl_fd("bash: cd: too few argument", 2);
		g_g.status = 1;
		return ;
	}
	if (tab[2] != NULL)
	{
		ft_putendl_fd("bash: cd: too many arguments", 2);
		g_g.status = 1;
		return ;
	}	
	if (chdir(tab[1]) == -1)
	{
		perror("chdir");
		g_g.status = 1;
		return ;
	}
	g_g.status = 0;
}

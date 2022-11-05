/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 20:06:46 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/05 09:51:52 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_size_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

void	ft_echo(char **tab)
{
	int	i;
	int size;

	i = 1;
	size = ft_size_tab(tab);
	while (i < size)
	{
		ft_putstr_fd(tab[i], STDOUT_FILENO);
		if (i + 1 != size)
			ft_putstr_fd(" ", STDOUT_FILENO);
		++i;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 20:06:46 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/12 19:10:22 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_n(char **tab, int *i)
{
	int	j;

	while (tab[*i])
	{
		j = -1;
		while (tab[*i][++j])
		{
			if (tab[*i][j] == '-')
			{
				if (tab[*i][j + 1] != 'n')
					return (0);
				while (tab[*i][j + 1] == 'n')
					j++;
				if (tab[*i][j + 1] == '\0')
				{
					(*i)++;
					return (1);
				}
			}
			else
				return (0);
		}
		(*i)++;
	}
	return (0);
}

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
	int	size;
	int	n;

	i = 1;
	size = ft_size_tab(tab);
	n = ft_check_n(tab, &i);
	if (n == 0)
		i = 1;
	while (i < size)
	{
		if (*tab[i] != 32)
			ft_putstr_fd(tab[i], STDOUT_FILENO);
		if (i + 1 != size)
			ft_putstr_fd(" ", STDOUT_FILENO);
		++i;
	}
	if (n == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_minishell.status = 0;
}

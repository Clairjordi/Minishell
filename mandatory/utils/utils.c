/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:07:17 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/24 14:50:04 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_len_va(char *var, int start, char c)
{
	int	i;

	i = start;
	while (var[i])
	{
		if (var[i] == c)
		{
			i++;
			return (i);
		}
		i++;
	}
	if (var[i] == '\0')
		i++;
	return (i);
}

char	**ft_realloc_tab_char(char **old_tab, char *new_var)
{
	char	**new_tab;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (old_tab[size] != NULL)
		size++;
	new_tab = ft_calloc(sizeof(char *), (size + 2));
	if (!new_tab)
		return (NULL);
	while (old_tab[i] != NULL)
	{
		new_tab[i] = old_tab[i];
		i++;
	}
	new_tab[i] = ft_strdup(new_var);
	i++;
	new_tab[i] = NULL;
	new_var = NULL;
	free(old_tab);
	return (new_tab);
}

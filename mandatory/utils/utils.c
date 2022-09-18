/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:07:17 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/18 17:09:33 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_realloc_tab_char(t_shell *shell, char **old_tab)
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
		ft_free_malloc(shell);
	while (old_tab[i] != NULL)
	{
		new_tab[i] = ft_strdup(old_tab[i]);
		i++;
	}
	new_tab[i] = ft_strdup(shell->test_add_env);
	i++;
	new_tab[i] = NULL;
	shell->test_add_env = NULL;
	ft_free_tab_char(old_tab);
	return (new_tab);
}

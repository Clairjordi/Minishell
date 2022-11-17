/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:10:44 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/16 18:59:46 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_count_words(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (ft_sep(s[i]) == 2 || ft_sep(s[i]) == 4)
			ft_skip_quote(&i, &s);
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	ft_slen(char *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i])
	{
		if (ft_sep(s[i]) == 2 || ft_sep(s[i]) == 4)
			len += ft_skip_quote(&i, &s);
		if (s[i] != c && s[i] != '\0')
			len++;
		else if (s[i] == '|')
			return (len);
		i++;
	}
	return (len);
}

char	**ft_split_pipes(char *s, char c)
{
	int		i;
	int		j;
	char	**tab_split;

	i = 0;
	j = 0;
	tab_split = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!tab_split)
		return (NULL);
	while (j < ft_count_words(s, c))
	{
		while (s[i] == c)
			i++;
		tab_split[j] = ft_substr(s, i, ft_slen(s, c, i));
		if (tab_split == NULL)
		{
			ft_free_tab_char(tab_split);
			return (NULL);
		}
		i = i + ft_slen(s, c, i);
		j++;
	}
	tab_split[j] = NULL;
	return (tab_split);
}

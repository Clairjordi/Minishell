/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:10:44 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/21 19:14:41 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\"' && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		else if (s[i] == '\"')
		{
			while (s[i] && s[i + 1] != '\"')
				i++;
			if ((s[i + 2] == c || s[i + 2] == '\0') && s[i] != '\"')
			{
				i++;
				count++;
			}
		}
		i++;
	}
	return (count);
}

static int	ft_slen(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		if (s[i] == '\"')
		{
			i++;
			len++;
			while (s[i] != '\"')
			{
				len++;
				i++;
			}
		}
		len++;
		i++;
	}
	return (len);
}

static void	ft_free(char **s, int i)
{
	while (i > 0)
	{
		free (s[i]);
		i--;
	}
	free (s);
}

char	**ft_test_split(char const *s, char c)
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
			ft_free(tab_split, j);
			return (NULL);
		}
		tab_split[j][ft_slen(s, c, i)] = '\0';
		i = i + ft_slen(s, c, i);
		j++;
	}
	tab_split[j] = NULL;
	return (tab_split);
}

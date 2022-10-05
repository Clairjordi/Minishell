/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:23:41 by mcloarec          #+#    #+#             */
/*   Updated: 2022/09/30 18:54:22 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_check_q(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

static int	ft_count_w(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (ft_check_q(s[i]) == 1)
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
		if (ft_check_q(s[i]) == 1)
			len += ft_skip_quote(&i, &s);
		if (s[i] != c && s[i] != '\0')
			len++;
		else
			break;
		i++;
	}
	return (len);
}

char	**ft_split_value(char *s, char c)
{
	int		i;
	int		j;
	char	**tab_split;

	i = 0;
	j = 0;
	tab_split = malloc(sizeof(char *) * (ft_count_w(s, c) + 1));
	if (!tab_split)
		return (NULL);
	while (j < ft_count_w(s, c))
	{
		while (s[i] == c)
			i++;
		tab_split[j] = ft_substr(s, i, ft_slen(s, c, i));
		if (tab_split == NULL)
		{
			ft_free_tab_char(tab_split);
			return (NULL);
		}
		tab_split[j][ft_slen(s, c, i)] = '\0';
		i = i + ft_slen(s, c, i);
		j++;
	}
	tab_split[j] = NULL;
	return (tab_split);
}

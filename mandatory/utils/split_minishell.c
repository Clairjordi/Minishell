/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:10:44 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/30 17:56:58 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_sep(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	else if (c == '\"')
		return (2);
	else if (c == '\'')
		return (4);
	else if (c == '<' || c == '>')
		return (3);
	return (0);
}

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
		tab_split[j][ft_slen(s, c, i)] = '\0';
		i = i + ft_slen(s, c, i);
		j++;
	}
	tab_split[j] = NULL;
	return (tab_split);
}
/*  */
/* static void	ft_quote(char c, int *p_i, int *p_count, char **p_s) */
/* { */
/* 	if (c == '\"') */
/* 	{ */
/* 		if ((*p_s)[*p_i + 1] == '\"') */
/* 		{ */
/* 				(*p_i)++; */
/* 			if (ft_sep((*p_s)[*p_i - 2]) != 1 && (*p_s)[*p_i + 1] == '\0') */
/* 				(*p_count)++; */
/* 		} */
/* 		else */
/* 		{ */
/* 			while ((*p_s)[*p_i] && (*p_s)[*p_i + 1] != '\"') */
/* 				(*p_i)++; */
/* 			if ((ft_sep((*p_s)[*p_i + 2]) == 1 */
/* 				|| (*p_s)[*p_i + 2] == '\0' */
/* 				|| ft_sep((*p_s)[*p_i + 2]) == 3) */
/* 				&& (*p_s)[*p_i] != '\"') */
/* 			{ */
/* 				(*p_i)++; */
/* 				(*p_count)++; */
/* 			} */
/* 		} */
/* 		if ((*p_s)[*p_i + 1] != '\0') */
/* 			(*p_i)++; */
/* 	} */
/* 	else if ((*p_s)[*p_i + 1] != '\0' && c == '\'') */
/* 	{ */
/* 		if ((*p_s)[*p_i + 1] == '\'') */
/* 		{ */
/* 				(*p_i)++; */
/* 			if (ft_sep((*p_s)[*p_i - 2]) != 1 && (*p_s)[*p_i + 1] == '\0') */
/* 				(*p_count)++; */
/* 		} */
/* 		else */
/* 		{ */
/* 			while ((*p_s)[*p_i] && (*p_s)[*p_i + 1] != '\'') */
/* 				(*p_i)++; */
/* 			if ((ft_sep((*p_s)[*p_i + 2]) == 1 */
/* 				|| (*p_s)[*p_i + 2] == '\0' */
/* 				|| ft_sep((*p_s)[*p_i + 2]) == 3) && (*p_s)[*p_i] != '\'') */
/* 			{ */
/* 				(*p_i)++; */
/* 				(*p_count)++; */
/* 			} */
/* 		} */
/* 		if ((*p_s)[*p_i + 1] != '\0') */
/* 			(*p_i)++; */
/* 	} */
/* } */
/*  */
/* static int	ft_count_words(char *s) */
/* { */
/* 	int	i; */
/* 	int	count; */
/*  */
/* 	i = 0; */
/* 	count = 0; */
/*  */
/* 	while (s[i] != '\0') */
/* 	{ */
/* 		if (s[i] && ((ft_sep(s[i]) == 3 && ft_sep(s[i + 1]) != 3) */
/* 			|| ((ft_sep(s[i]) != 1 && ft_sep(s[i]) != 2 && ft_sep(s[i]) != 3 */
/* 					&& (ft_sep(s[i + 1]) == 3 || ft_sep(s[i + 1]) == 1 */
/* 						|| s[i + 1] == '\0'))))) */
/* 			count++; */
/* 		else if (ft_sep(s[i]) == 2) */
/* 			ft_quote(s[i], &i, &count, &s); */
/* 		if (s[i] != '\'' && s[i] != '\"' && s[i + 1] == '\0') */
/* 			count++; */
/* 		i++; */
/* 	} */
/* 	return (count); */
/* } */
/*  */
/* static int	ft_slen(char *s, int i) */
/* { */
/* 	int	len; */
/* 	char	c; */
/*  */
/* 	len = 0; */
/* 	while (s[i] && ft_sep(s[i]) != 1) */
/* 	{ */
/* 		if (ft_sep(s[i]) == 2) */
/* 		{ */
/* 			if (s[i] == '\"') */
/* 				 c = '\"'; */
/* 			else if (s[i] == '\'') */
/* 				c = '\''; */
/* 			i++; */
/* 			len++; */
/* 			while (s[i] != c) */
/* 			{ */
/* 				len++; */
/* 				i++; */
/* 			} */
/* 		} */
/* 		if (ft_sep(s[i]) == 3 && ft_sep(s[i + 1]) != 1 */
/* 			&& ft_sep(s[i + 1]) != 3) */
/* 			return (len + 1); */
/* 		if (ft_sep(s[i + 1]) == 3 && ft_sep(s[i]) != 1 && ft_sep(s[i]) != 3) */
/* 			return (len + 1); */
/* 		len++; */
/* 		i++; */
/* 	} */
/* 	return (len); */
/* } */



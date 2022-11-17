/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:43:15 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/16 18:54:24 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_skip_quote(int *i, char **s)
{
	int		size;
	char	c;

	size = 0;
	if (ft_sep((*s)[*i]) == 2)
		c = '\"';
	else if (ft_sep((*s)[*i]) == 4)
		c = '\'';
	else
		return (size);
	while ((*s)[*i + 1] != c && (*s)[*i + 1] != '\0')
	{
		(*i)++;
		size++;
	}
	if ((*s)[*i + 1] != '\0')
	{
		(*i)++;
		size++;
	}
	return (size);
}

char	*ft_delete_quotes_redirect(t_shell *shell, char *s)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = NULL;
	while (s[i])
	{
		shell->quote = ft_open_quote(shell, s[i]);
		if ((shell->quote == 2 && s[i] != '\"')
			|| (shell->quote == 1 && s[i] != '\''))
		{
			new_str = ft_charjoin(new_str, s[i]);
			if (new_str == NULL)
				ft_free_malloc(shell);
		}
		i++;
	}
	free(s);
	return (new_str);
}

void	ft_check_c(char **str, int *d, int *s, int *i)
{
	if ((*str)[*i] == '\"')
	{
		(*d)++;
		while ((*str)[*i] && (*str)[*i + 1] != '\"' && (*str)[*i + 1] != '\0')
			(*i)++;
		if ((*str)[++(*i)] == '\"')
			(*d)++;
	}
	else if ((*str)[*i] == '\'')
	{
		(*s)++;
		while ((*str)[*i] && (*str)[*i + 1] != '\'' && (*str)[*i + 1] != '\0')
			(*i)++;
		if ((*str)[++(*i)] == '\'')
			(*s)++;
	}
}

int	ft_count_quote(char *str)
{
	int	i;
	int	dble;
	int	simple;

	i = 0;
	dble = 0;
	simple = 0;
	while (str[i])
	{
		ft_check_c(&str, &dble, &simple, &i);
		if (str[i] != '\0')
			i++;
	}
	if (dble % 2 != 0 || simple % 2 != 0)
	{
		ft_putendl_fd("Wrong quotes syntax", 2);
		g_minishell.status = 1;
		return (-1);
	}
	return (0);
}

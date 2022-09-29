/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:43:15 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/28 12:07:45 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_skip_quote(int *i, char **s)
{
	int	size;

	size = 0;
	if (ft_sep((*s)[*i]) == 2)
	{
		while (ft_sep((*s)[*i + 1]) != 2 && (*s)[*i + 1] != '\0')
		{
			(*i)++;
			size++;
		}
		if ((*s)[*i + 1] != '\0')
		{
			(*i)++;
			size++;
		}
	}
	return (size);
}

int	ft_len_without_quote(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] != '\"')
			size++;
		i++;
	}
	return (size);
}

char	*ft_delete_quotes(char *str, t_shell *shell)
{
	int		i;
	char	*new_str;
	int		size;
	int		size_copy;

	size = ft_len_without_quote(str);
	new_str = ft_calloc(sizeof(char *), (size + 1));
	if (!new_str)
		ft_free_malloc(shell);
	i = 0;
	size_copy = 0;
	while (str[i])
	{
		if (str[i] != '\"')
		{
			new_str[size_copy] = str[i];
			size_copy++;
		}
		i++;
	}
	free(str);
	new_str[size_copy] = '\0';
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
		return (-1);
	}
	return (0);
}

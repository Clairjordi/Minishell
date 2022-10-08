/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:44:30 by mcloarec          #+#    #+#             */
/*   Updated: 2022/10/08 11:06:52 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_redirect(char *s)
{
	int		size;
	int		i;
	char	c;

	i = 0;
	while (s[i])
	{
		size = 0;
		ft_skip_quote(&i, &s);
		if (ft_sep(s[i]) == 3)
		{
			c = s[i];
			while (s[i] && s[i] == c)
			{
				i++;
				size++;
			}
			if ((size > 2 && size % 2 != 0) || (i == 2 && s[i] == '\0') )
			{
				ft_putendl_fd("Wrong redirection syntax", 2);
				return (-1);
			}
		}
		if (s[i] != '\0')
			i++;
	}
	return (0);
}

int	ft_verif_redirect(char *s)
{
	int		i;

	i = 0;
	if (ft_sep(s[i]) == 3 && s[i + 1] == '\0')
	{
		ft_putendl_fd("Wrong redirection syntax", 2);
		return (-1);
	}
	if (ft_check_redirect(s) == -1)
		return (-1);
	while (s[i])
	{
		ft_skip_quote(&i, &s);
		if ((s[i] == '<' && s[i + 1] == '>')
			|| (s[i] == '>' && s[i + 1] == '<'))
		{
			ft_putendl_fd("Wrong redirection syntax", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

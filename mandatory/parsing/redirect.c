/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:44:30 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/16 18:52:24 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_not_redirection(char *s)
{
	int		i;
	char	redirect;

	i = 0;
	redirect = 'n';
	while (s[i])
	{
		if (ft_sep(s[i]) == 3)
			redirect = 'o';
		if (ft_sep(s[i]) != 3 && ft_check_q(s[i]) != 1)
			return (FALSE);
		i++;
	}
	if (redirect == 'n')
		return (FALSE);
	return (TRUE);
}

int	ft_valid_redirect(char *s)
{
	if (ft_strcmp(s, "<<") == 0)
		return (1);
	if (ft_strcmp(s, "<") == 0)
		return (2);
	if (ft_strcmp(s, ">>") == 0)
		return (3);
	if (ft_strcmp(s, ">") == 0)
		return (4);
	return (FALSE);
}

static int	ft_check_redirect_bis(int *i, int size, char *s)
{
	char	c;

	c = s[*i];
	while (s[*i] && s[*i] == c)
	{
		(*i)++;
		size++;
	}
	if (size > 2 || (*i == 2 && s[*i] == '\0'))
		return (-1);
	return (0);
}

int	ft_check_redirect(char *s)
{
	int		size;
	int		i;

	i = 0;
	while (s[i])
	{
		size = 0;
		ft_skip_quote(&i, &s);
		if (ft_sep(s[i]) == 3)
		{
			if (ft_check_redirect_bis(&i, size, s) == -1)
			{
				ft_putendl_fd("Wrong redirection syntax", 2);
				g_minishell.status = 2;
				return (-1);
			}
		}
		else if (s[i] != '\0')
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
		g_minishell.status = 2;
		return (-1);
	}
	if (ft_check_redirect(s) == -1)
		return (-1);
	while (s[i])
	{
		ft_skip_quote(&i, &s);
		if ((s[i] == '>' && s[i + 1] == '<')
			|| (s[i] == '<' && s[i + 1] == '>'))
		{
			ft_putendl_fd("Wrong redirection syntax", 2);
			g_minishell.status = 2;
			return (-1);
		}
		i++;
	}
	return (0);
}

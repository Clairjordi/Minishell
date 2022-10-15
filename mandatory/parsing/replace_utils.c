/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:34:30 by mcloarec          #+#    #+#             */
/*   Updated: 2022/10/15 14:17:06 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_redir(char *s)
{
	int	redir;
	int	i;

	redir = 0;
	i = 0;
	while (s[i])
	{
		if (ft_sep(s[i]) == 3)
			redir++;
		else if (ft_sep(s[i]) != 3 && ft_check_q(s[i]) == 0)
		{
			redir = 0;
			break ;
		}
		i++;
	}
	return (redir);
}

int	ft_open_quote(t_shell *shell, char c)
{
	if (c == '\"')
	{
		if (shell->quote == 2)
			shell->quote = 0;
		else if (shell->quote == 1)
			shell->quote = 1;
		else
			shell->quote = 2;
	}
	else if (c == '\'')
	{
		if (shell->quote == 1)
			shell->quote = 0;
		else if (shell->quote == 2)
			shell->quote = 2;
		else
			shell->quote = 1;
	}
	return (shell->quote);
}

char	*ft_rep_quotes_space(t_shell *shell, int i, int *j, t_cmds *lst)
{
	char	*space;

	space = NULL;
	if (ft_sep(lst->value_split[i][*j]) == 2
			&& ft_sep(lst->value_split[i][*j + 1]) == 2
			&& lst->value_split[i][*j + 2] == '\0')
	{
		space = ft_charjoin(shell->tmp, ' ');
		if (space == NULL)
			ft_free_malloc(shell);
	}
	else if (ft_sep(lst->value_split[i][*j]) == 4
			&& ft_sep(lst->value_split[i][*j + 1]) == 4
			&& lst->value_split[i][*j + 2] == '\0')
	{
		space = ft_charjoin(shell->tmp, ' ');
		if (space == NULL)
			ft_free_malloc(shell);
	}
	return (space);
}

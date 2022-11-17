/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:34:30 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/17 16:21:50 by clorcery         ###   ########.fr       */
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

char	*ft_rep_quotes_space(int i, int *j, t_cmds *lst)
{
	char	*space;

	space = NULL;
	if (ft_sep(lst->value_split[i][*j]) == 2
			&& ft_sep(lst->value_split[i][*j + 1]) == 2
			&& lst->value_split[i][*j + 2] == '\0')
		space = ft_cdup('\0');
	else if (ft_sep(lst->value_split[i][*j]) == 4
			&& ft_sep(lst->value_split[i][*j + 1]) == 4
			&& lst->value_split[i][*j + 2] == '\0')
		space = ft_cdup('\0');
	return (space);
}

void	ft_realloc_value_split(t_shell *shell, int *i, t_cmds *lst)
{
	char	**value_space;
	int		j;

	j = 1;
	value_space = NULL;
	value_space = ft_split(shell->tmp, ' ');
	if (value_space == NULL)
		ft_free_malloc(shell);
	lst->value_split[*i] = ft_free_ptr(lst->value_split[*i]);
	lst->value_split[*i] = ft_strdup(value_space[0]);
	ft_verif_malloc(shell, lst->value_split[*i]);
	while (value_space[j] != NULL)
	{
		lst->value_split = ft_realloc_tab_char(lst->value_split,
				value_space[j]);
		(*i)++;
		j++;
	}
	ft_free_tab_char(value_space);
}

void	ft_verif_space_value(t_shell *shell, int *i, t_cmds *lst)
{
	int	j;

	j = 0;
	while (shell->tmp[j])
	{
		if (shell->tmp[j] == ' ')
		{
			ft_realloc_value_split(shell, i, lst);
			free(shell->tmp);
			return ;
		}
		j++;
	}
	if (shell->tmp[j] == '\0')
	{
		lst->value_split[*i] = ft_free_ptr(lst->value_split[*i]);
		lst->value_split[*i] = shell->tmp;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:54:59 by mcloarec          #+#    #+#             */
/*   Updated: 2022/10/13 18:51:58 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*ft_rep(t_shell *shell, int i, int *j, t_cmds *lst)
{
	char	*new;

	/* while (lst->value_split[i][*j] == '$') */
	/* 	(*j)++; */
	if (ft_check_q(lst->value_split[i][*j]) == 1)
	{
		new = ft_rep_quotes_space(shell, i, j, lst);
		if (new)
		{
			(*j)++;
			return (new);
		}
	}
	new = shell->tmp;
	shell->quote = ft_open_quote(shell, lst->value_split[i][*j]);
	if (!(lst->value_split[i][*j] == '\'' && shell->quote != 2)
			&& !(lst->value_split[i][*j] == '\"' && shell->quote != 1))
	{
		new = ft_charjoin(shell->tmp, lst->value_split[i][*j]);
		if (new == NULL)
			ft_free_malloc(shell);
	}
	return (new);
}

int	ft_replace_value_split(t_shell *shell, int i, t_cmds *lst)
{
	if (shell->tmp != NULL)
	{
		lst->value_split[i] = ft_free_ptr(lst->value_split[i]);
		lst->value_split[i] = shell->tmp;
	}
	/* else */
	/* 	return (-1); */
	return (0);
}

int	ft_replace_value(t_shell *shell)
{
	int		i;
	int		j;
	t_cmds	*lst;

	lst = shell->arg;
	while (lst != NULL)
	{
		i = 0;
		while (lst->value_split[i] != NULL)
		{
			shell->tmp = NULL;
			shell->dollar = ft_check_dollar(shell, lst->value_split[i]);
			j = 0;
			while (lst->value_split[i][j])
			{
				if (lst->value_split[i][j] == '$' && shell->dollar != 0)
					shell->tmp = ft_rep_if_dollar(shell, i, &j, lst);
				else
					shell->tmp = ft_rep(shell, i, &j, lst);
				if (lst->value_split[i][j] != '\0')
					j++;
			}
			if (ft_replace_value_split(shell, i, lst) == -1)
				return (-1);
			i++;
		}
		/* i = 0; */
		/* if (shell->test == 0) */
		/* { */
		/* 	while (lst->value_split[i + 1] != NULL) */
		/* 	{ */
		/* 		lst->value_split[i] = lst->value_split[i + 1]; */
		/* 		ft_free_ptr(lst->value_split[i + 1]); */
		/* 		lst->value_split[i + 1] = NULL; */
		/* 		i++; */
		/* 	} */
		/* } */
		lst = lst->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:35:26 by mcloarec          #+#    #+#             */
/*   Updated: 2022/10/20 18:20:05 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	return (0);
}

int	ft_check_error_redirect(t_shell *shell)
{
	int		i;
	t_cmds	*lst;

	i = 0;
	lst = shell->arg;
	while (lst)
	{
		i = 0;
		while (lst->value_split[i] != NULL)
		{
			if (ft_valid_redirect(lst->value_split[i]) != 0
				&& (lst->value_split[i + 1] == NULL
					|| ft_valid_redirect(lst->value_split[i + 1]) != 0))
			{
				ft_free(shell, "Syntax error near unexpected token");
				g_g.status = 2;
				return (FALSE);
			}
			i++;
		}
		lst = lst->next;
	}
	return (TRUE);
}

/* void	ft_check_infile(t_shell *shell) */
/* { */
/*  */
/* } */

void	ft_minishell(t_shell *shell, char **envp)
{
	(void) envp;
	if (ft_check_error_redirect(shell) == FALSE)
		return ;
	ft_init_heredoc(shell);
	//ft_check_infile(shell);
	/* if (ft_sort_value(shell, envp) == -1) */
	/* 	return (-1); */
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:31:44 by mcloarec          #+#    #+#             */
/*   Updated: 2022/10/17 18:07:49 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_if_redirect(t_shell *shell, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '<')
			shell->arg->redir_l = 1;
		else if (s[i] == '>')
			shell->arg->redir_r = 1;
		else if (s[i] == '<' && s[i + 1] == '<')
			shell->arg->heredoc = 1;
		else if (s[i] == '>' && s[i + 1] == '>')
			shell->arg->append = 1;
		else
			return (-1);
		i++;
	}
	return (0);
}

/* void	ft_sort_value_bis(t_shell *shell, char **envp) */
/* { */
/* 	(void) envp; */
/* 	(void) shell; */
/* 	ft_printf("bis\n"); */
/* } */


int	ft_sort_value(t_shell *shell, char **envp)
{
	t_cmds	*lst;
	int		i;

	i = 0;
	lst = shell->arg;
	while (lst)
	{
		if (i == 0)
		{
			if (get_path(shell, lst->value_split[i], envp) == -1
				&& ft_if_redirect(shell, lst->value_split[i]) == -1)
				ft_putendl_fd("First arg must be cmd or redirection", 2);
			else
				ft_printf("cool\n");
		}
		ft_sort_value_bis(shell, envp);
		lst = lst->next;
	}
	return (0);
}

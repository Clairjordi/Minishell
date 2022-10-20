/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:31:44 by mcloarec          #+#    #+#             */
/*   Updated: 2022/10/20 17:31:27 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* int	ft_if_redirect(t_shell *shell, char *s) */
/* { */
/* 	int	i; */
/*  */
/* 	i = 0; */
/* 	while (s[i]) */
/* 	{ */
/* 		if (s[i] == '<') */
/* 			shell->arg->redir_l = 1; */
/* 		else if (s[i] == '>') */
/* 			shell->arg->redir_r = 1; */
/* 		else if (s[i] == '<' && s[i + 1] == '<') */
/* 			shell->arg->hdoc = 1; */
/* 		else if (s[i] == '>' && s[i + 1] == '>') */
/* 			shell->arg->append = 1; */
/* 		else */
/* 			return (-1); */
/* 		i++; */
/* 	} */
/* 	return (0); */
/* } */

/* void	ft_sort_value_bis(t_shell *shell, char **envp) */
/* { */
/* 	(void) envp; */
/* 	(void) shell; */
/* 	ft_printf("bis\n"); */
/* } */

/*void	ft_malloc_double_char(t_shell *shell, t_cmds *lst, int i)
{
	int	size;

	size = 0;
	while (lst->value_split[i] != NULL
		&& ft_if_redirect(shell, lst->value_split[i]) == -1)
	{
		size++;
		i++;
	}
	shell->test_cmd = malloc(sizeof(char *) *(size + 1));
}

int	ft_sort_value(t_shell *shell, char **envp)
{
	t_cmds	*lst;
	int		i;
	int		file;
	int		j;

	shell->test_cmd = NULL;
	shell->in = 0;
	lst = shell->arg;
	while (lst)
	{
		i = 0;
		while (lst->value_split[i] != NULL)
		{
			j = 0;
			if (ft_strcmp(lst->value_split[i], "<") == 0)
			{
				file = open(lst->value_split[i + 1], O_RDONLY);
				if (file != -1)
					shell->in = 1;
				else
				{
					ft_putendl_fd("the file doesn't exit", 2);
					break ;
				}
				i++;
			}
			else if (get_path(shell, lst->value_split[i], envp) == 0)
			{
				ft_printf("ici\n");
				ft_malloc_double_char(shell, lst, i);
				while (lst->value_split[i] != NULL
					&& ft_if_redirect(shell, lst->value_split[i]) == -1)
				{
					shell->test_cmd[j] = ft_strdup(lst->value_split[i]);
					j++;
					i++;
				}
			}
			if (lst->value_split[i] != NULL)
				i++;
		}
		lst = lst->next;
	}
	j = 0;
	while (shell->test_cmd != NULL && shell->test_cmd[j] != NULL)
		ft_printf("shell->test : %s\n", shell->test_cmd[j++]);
	ft_printf("shell->in = %d\n", shell->in);
	ft_printf("|| =^^= | =^^= | =^^= ||\n");
	if (shell->in == 1)
		close(file);
	return (0);
}*/

/* int	ft_sort_value(t_shell *shell, char **envp) */
/* { */
/* 	t_cmds	*lst; */
/* 	int		i; */
/*  */
/* 	i = 0; */
/* 	lst = shell->arg; */
/* 	while (lst) */
/* 	{ */
/* 		if (i == 0) */
/* 		{ */
/* 			if (get_path(shell, lst->value_split[i], envp) == -1 */
/* 				&& ft_if_redirect(shell, lst->value_split[i]) == -1) */
/* 				ft_putendl_fd("First arg must be cmd or redirection", 2); */
/* 			else */
/* 				ft_printf("cool\n"); */
/* 		} */
/* 		ft_sort_value_bis(shell, envp); */
/* 		lst = lst->next; */
/* 	} */
/* 	return (0); */
/* } */

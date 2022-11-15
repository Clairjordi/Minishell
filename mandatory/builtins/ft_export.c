/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 09:28:03 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/15 14:17:09 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_write_export(t_envcpy *env)
{
	t_envcpy	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->name, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd("\"", 1);
		if (tmp->value != NULL)
			ft_putstr_fd(tmp->value, 1);
		ft_putendl_fd("\"", 1);
		tmp = tmp->next;
	}
	g_minishell.status = 0;
}

int	ft_name_var(char *s)
{
	int	i;

	i = 0;
	if (ft_isalpha(s[0]) == 1 || s[0] == '_')
		i++;
	while (s[i])
	{
		while (ft_isalnum(s[i]) == 1)
			i++;
		if (s[i] == '=')
			return (1);
		if (s[i] == '\0')
			return (2);
		if (s[i] == '+' && s[i + 1] == '=')
			return (3);
		else
			break ;
	}
	return (0);
}

int	ft_check_name_var(char *s)
{
	int	check;

	check = 0;
	if (ft_isalpha(s[0]) == 0 && s[0] != '_')
	{
		ft_putendl_fd("bash : unset: not a valid identifier", 2);
		g_minishell.status = 1;
		return (check);
	}
	check = ft_name_var(s);
	if (check == 1)
		return (1);
	else if (check == 2)
		return (2);
	else if (check == 3)
		return (3);
	return (check);
}

int	ft_modify_var(t_shell *shell, int check, int i)
{
	if (check == 1)
	{
		ft_check_var(shell->env->first, shell->exec->builtins[i]);
		ft_check_var(shell->env->head, shell->exec->builtins[i]);
		return (TRUE);
	}
	else if (check == 2)
	{
		ft_add_export(shell->env->head, shell->exec->builtins[i]);
		return (TRUE);
	}
	/* else if (check == 3) */
	/* { */
	/* 	ft_append_var(shell->env->first, shell->exec->builtins[i]); */
	/* 	ft_append_var(shell->env->head, shell->exec->builtins[i]); */
	/* 	return (TRUE); */
	/* } */
	return (FALSE);
}

void	ft_export(t_shell *shell)
{
	int			i;
	int			check;

	i = 1;
	check = 0;
	if (ft_size_tab(shell->exec->builtins) == 1)
	{
		ft_sorted_by_ascii(shell->env->head);
		ft_write_export(shell->env->head);
		return ;
	}
	while (shell->exec->builtins[i])
	{
		check = ft_check_name_var(shell->exec->builtins[i]);
		if (ft_modify_var(shell, check, i) == FALSE)
			break ;
		i++;
	}
	g_minishell.status = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 09:28:03 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/17 17:28:34 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_name_var(char *s)
{
	int	i;

	i = 0;
	if (ft_isalpha(s[0]) == 1 || s[0] == '_')
		i++;
	if (s[i] == '\0')
		return (2);
	while (s[i])
	{
		while (ft_isalnum(s[i]) == 1)
			i++;
		if (s[i] == '=')
			return (1);
		if (s[i] == '\0')
			return (2);
		if (s[i] == '+')
		{
			i++;
			if (s[i] == '=')
				return (3);
		}
		else
			break ;
	}
	return (0);
}

int	ft_check_existing_var(t_env *env, char *s)
{
	char		*var;
	t_envcpy	*var_env;
	t_envcpy	*var_export;

	var = NULL;
	var_env = NULL;
	var_export = NULL;
	var = ft_get_name_export(s);
	if (var != NULL)
	{
		var_env = ft_check_name_envcpy(env->first, var);
		if (var_env != NULL)
		{
			free(var);
			return (TRUE);
		}
		var_export = ft_check_name_envcpy(env->head, var);
		if (var_export != NULL)
		{
			free(var);
			return (TRUE);
		}
		free(var);
	}
	return (FALSE);
}

int	ft_check_name_var(t_env *env, char *s)
{
	int			check;

	check = 0;
	if (ft_isalpha(s[0]) == 0 && s[0] != '_')
		return (check);
	check = ft_name_var(s);
	if (check == 1)
		return (1);
	else if (check == 2)
		return (2);
	else if (check == 3)
	{
		if (ft_check_existing_var(env, s) == FALSE)
			return (1);
		else
			return (3);
	}
	return (check);
}

int	ft_modify_var(t_shell *shell, int check, int i)
{
	if (check == 1)
	{
		ft_check_var(shell, shell->env->first, shell->exec->builtins[i]);
		ft_check_var(shell, shell->env->head, shell->exec->builtins[i]);
		return (TRUE);
	}
	else if (check == 2)
	{
		ft_add_var_env(shell, shell->env->head, shell->exec->builtins[i]);
		return (TRUE);
	}
	else if (check == 3)
	{
		ft_append_var(shell, shell->env->first, shell->exec->builtins[i]);
		ft_append_var(shell, shell->env->head, shell->exec->builtins[i]);
		return (TRUE);
	}
	else
	{
		ft_putendl_fd("bash : export: not a valid identifier", 2);
		g_minishell.status = 1;
		return (check);
	}
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
		ft_write_export(shell, shell->env->head);
		return ;
	}
	while (shell->exec->builtins[i])
	{
		check = ft_check_name_var(shell->env, shell->exec->builtins[i]);
		if (check == 0)
		{
			ft_putendl_fd("bash : export: not a valid identifier", 2);
			g_minishell.status = 1;
			return ;
		}
		else if (ft_modify_var(shell, check, i) == FALSE)
			break ;
		i++;
	}
	g_minishell.status = 0;
}

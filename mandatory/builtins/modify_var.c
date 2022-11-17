/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:26:04 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/17 16:21:41 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_free_append_var(char *name, char *value_add, char *value,
		char *var_add)
{
	free(name);
	free(value_add);
	free(value);
	free(var_add);
}

void	ft_append_var(t_shell *shell, t_envcpy *lst, char *s)
{
	t_envcpy	*var;
	char		*name;
	char		*value_add;
	char		*value;
	char		*var_add;

	name = ft_get_name_export(s);
	ft_verif_malloc(shell, name);
	var = ft_check_name_envcpy(lst, name);
	value_add = ft_get_value_export(shell, s);
	ft_verif_malloc(shell, value_add);
	value = ft_strdup(var->value);
	ft_verif_malloc(shell, value);
	var_add = ft_strdup(var->var);
	ft_verif_malloc(shell, var_add);
	if (var != NULL)
	{
		free(var->value);
		var->value = ft_strjoin(value, value_add);
		ft_verif_malloc(shell, var->value);
		free(var->var);
		var->var = ft_strjoin(var_add, value_add);
		ft_verif_malloc(shell, var->var);
	}
	ft_free_append_var(name, value_add, value, var_add);
}

void	ft_change_var(t_shell *shell, t_envcpy *lst, char *s)
{
	char	*value;

	value = ft_get_value_export(shell, s);
	ft_verif_malloc(shell, value);
	free(lst->value);
	lst->value = ft_strdup(value);
	ft_verif_malloc(shell, lst->value);
	free(lst->var);
	lst->var = ft_strdup(s);
	ft_verif_malloc(shell, lst->var);
	free(value);
}

void	ft_check_var(t_shell *shell, t_envcpy *lst, char *s)
{
	t_envcpy	*var;
	char		*name;

	name = ft_get_name_env(shell, s);
	ft_verif_malloc(shell, name);
	var = ft_check_name_envcpy(lst, name);
	if (var == NULL)
		ft_add_var_env(shell, lst, s);
	else
		ft_change_var(shell, var, s);
	free(name);
}

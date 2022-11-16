/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:26:04 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/16 10:43:22 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_append_var(t_envcpy *lst, char *s)
{
	t_envcpy	*var;
	char		*name;
	char		*value_add;
	char		*value;
	char		*var_add;

	name = ft_get_name_export(s);
	var = ft_check_name_envcpy(lst, name);
	value_add = ft_get_value_export(s);
	value = ft_strdup(var->value);
	var_add = ft_strdup(var->var);
	if (var != NULL)
	{
		free(var->value);
		var->value = ft_strjoin(value, value_add);
		free(var->var);
		var->var = ft_strjoin(var_add, value_add);
	}
	free(name);
	free(value_add);
	free(value);
	free(var_add);
}

void	ft_change_var(t_envcpy *lst, char *s)
{
	char	*value;

	value = ft_get_value_export(s);
	free(lst->value);
	lst->value = ft_strdup(value);
	free(lst->var);
	lst->var = ft_strdup(s);
	free(value);
}

void	ft_check_var(t_envcpy *lst, char *s)
{
	t_envcpy	*var;
	char		*name;

	name = ft_get_name(s);
	var = ft_check_name_envcpy(lst, name);
	if (var == NULL)
		ft_add_var_env(lst, s);
	else
		ft_change_var(var, s);
	free(name);
}

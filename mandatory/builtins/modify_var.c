/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:26:04 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/15 15:36:47 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_change_var_env(t_envcpy *lst, char *s)
{
	char	*value;

	value = ft_get_value_export(s);
	free(lst->value);
	lst->value = ft_strdup(value);
	free(lst->var);
	lst->var = ft_strdup(s);
	free(value);
}

void	ft_change_var(t_envcpy *lst, char *s)
{
	char	*value;

	value = ft_get_value_export(s);
	free(lst->value);
	lst->value = ft_strdup(value);
	free(value);
}

void	ft_check_var(t_envcpy *lst, char *s)
{
	t_envcpy	*var;
	char		*name;

	name = ft_get_name(s);
	var = ft_check_name_envcpy(lst, name);
	if (var == NULL)
	{
		if (ft_strcmp(lst->name, "COLORTERM") == 0)
			ft_add_export(lst, s);
		else
			ft_add_var_env(lst, s);
	}
	else
	{
		if (ft_strcmp(var->prev->name, "COLORTERM") == 0)
			ft_change_var(var, s);
		else
			ft_change_var_env(var, s);
	}
	free(name);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getexport_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:07:49 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/14 16:44:53 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_env_cpy(t_envcpy *cpy)
{
	t_envcpy	*tmp;
	t_envcpy	*buf;

	if (cpy == NULL)
		return ;
	tmp = cpy;
	while (tmp)
	{
		buf = tmp->next;
		if (tmp->name != NULL)
			free(tmp->name);
		if (tmp->value != NULL)
			free(tmp->value);
		free(tmp);
		tmp = buf;
	}
}

void	ft_swap_var(t_envcpy *current, t_envcpy *next)
{
	char		*name;
	char		*value;
	char		*var;

	name = current->name;
	value = current->value;
	var = current->var;
	current->name = next->name;
	current->value = next->value;
	current->var = next->var;
	next->name = name;
	next->value = value;
	next->var = var;
}

void	ft_check_sorted(t_envcpy *sorted)
{
	t_envcpy	*check;

	check = sorted;
	while (check->next)
	{
		if (ft_strcmp(check->next->name, check->name) > 0)
		{
			ft_swap_var(check, check->next);
			check = sorted;
		}
		check = check->next;
	}
}

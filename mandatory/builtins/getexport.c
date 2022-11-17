/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getexport.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:05:07 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/17 16:46:06 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envcpy	*ft_cpy_env(t_shell *shell, t_envcpy *env_lst)
{
	t_envcpy	*new;

	new = malloc(sizeof(t_envcpy));
	if (!new)
		ft_free_malloc(shell);
	new->name = ft_strdup(env_lst->name);
	ft_verif_malloc(shell, new->name);
	new->value = ft_strdup(env_lst->value);
	ft_verif_malloc(shell, new->value);
	new->var = ft_strdup(env_lst->var);
	ft_verif_malloc(shell, new->var);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	ft_create_lst_export(t_shell *shell)
{
	t_envcpy	*tmp;
	t_envcpy	*add;
	t_envcpy	*cpy;

	shell->env->head = ft_cpy_env(shell, shell->env->first);
	tmp = shell->env->head;
	cpy = shell->env->first;
	cpy = cpy->next;
	while (cpy)
	{
		add = ft_cpy_env(shell, cpy);
		tmp->next = add;
		add->prev = tmp;
		tmp = add;
		cpy = cpy->next;
	}
}

void	ft_sorted_by_ascii(t_envcpy *export)
{
	t_envcpy	*tmp;
	t_envcpy	*sorted;

	sorted = export;
	tmp = sorted;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->next->name, tmp->name) > 0)
		{
			ft_swap_var(tmp, tmp->next);
			tmp = sorted;
		}
		tmp = tmp->next;
	}
	ft_check_sorted(sorted);
}

void	ft_getexport(t_shell *shell)
{
	ft_create_lst_export(shell);
	ft_sorted_by_ascii(shell->env->head);
}

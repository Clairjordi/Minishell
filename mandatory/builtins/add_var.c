/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:54:24 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/17 16:22:41 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_value_export(t_shell *shell, char *s)
{
	char	*value;

	value = NULL;
	while ((*s && *s != '=') && (*s && *s != '+'))
		s++;
	if (*s != '+' && *s != '=')
	{
		if (*s == '+')
			s++;
		if (*s + 1 != '\0' && *s != '=')
		{
			value = ft_cdup('\0');
			ft_verif_malloc(shell, value);
			return (value);
		}
	}
	if (*s + 1 != '\0' && (*s == '+' || *s == '='))
	{
		s++;
		if (*s == '=')
			s++;
	}
	value = ft_create_value_export(s);
	return (value);
}

t_envcpy	*ft_add_new_export(t_shell *shell, char *s)
{
	t_envcpy	*new;

	new = malloc(sizeof(t_envcpy));
	if (!new)
		ft_free_malloc(shell);
	new->name = ft_get_name_env(shell, s);
	ft_verif_malloc(shell, new->name);
	new->value = ft_get_value_export(shell, s);
	ft_verif_malloc(shell, new->value);
	new->var = ft_strjoin(new->name, new->value);
	ft_verif_malloc(shell, new->var);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_envcpy	*ft_add_new_env(t_shell *shell, char *s)
{
	t_envcpy	*new;
	char		*sign;
	char		*tmp;

	new = malloc(sizeof(t_envcpy));
	if (!new)
		ft_free_malloc(shell);
	sign = ft_cdup('=');
	ft_verif_malloc(shell, sign);
	new->name = ft_get_name_env(shell, s);
	ft_verif_malloc(shell, new->name);
	new->value = ft_get_value_export(shell, s);
	ft_verif_malloc(shell, new->value);
	tmp = ft_strjoin(new->name, sign);
	ft_verif_malloc(shell, tmp);
	new->var = ft_strjoin(tmp, new->value);
	free(tmp);
	free(sign);
	ft_verif_malloc(shell, new->var);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	ft_add_var_env(t_shell *shell, t_envcpy *env, char *s)
{
	t_envcpy	*new;
	t_envcpy	*tmp;
	t_envcpy	*next;

	tmp = env;
	if (ft_strcmp(tmp->name, "COLORTERM") == 0)
		new = ft_add_new_export(shell, s);
	else
		new = ft_add_new_env(shell, s);
	next = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = next;
	next->prev = new;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:54:24 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/15 15:41:36 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_value_export(char *s)
{
	int		i;
	int		len;
	char	*value;

	while (*s && *s != '=')
		s++;
	if (*s != '=')
		return (NULL);
	s++;
	len = ft_strlen(s);
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	i = 0;
	while (*s)
	{
		value[i] = *s;
		s++;
		i++;
	}
	value[i] = '\0';
	return (value);
}

t_envcpy	*ft_add_new_export(char *s)
{
	t_envcpy	*new;

	new = malloc(sizeof(t_envcpy));
	if (!new)
		return (NULL);
	new->name = ft_get_name(s);
	new->value = ft_get_value_export(s);
	new->var = ft_strdup(s);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_envcpy	*ft_add_new_env(char *s)
{
	t_envcpy	*new;

	new = malloc(sizeof(t_envcpy));
	if (!new)
		return (NULL);
	new->name = ft_get_name(s);
	new->value = ft_get_value_export(s);
	new->var = ft_strdup(s);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	ft_add_var_env(t_envcpy *env, char *s)
{
	t_envcpy	*new;
	t_envcpy	*tmp;
	t_envcpy	*next;

	tmp = env;
	new = ft_add_new_env(s);
	next = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = next;
	next->prev = new;
}

void	ft_add_export(t_envcpy *export, char *s)
{
	t_envcpy	*new;
	t_envcpy	*tmp;
	t_envcpy	*next;

	tmp = export;
	new = ft_add_new_export(s);
	next = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = next;
	next->prev = new;
}

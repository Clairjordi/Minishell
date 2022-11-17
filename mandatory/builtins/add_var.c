/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:54:24 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/17 13:28:24 by mcloarec         ###   ########.fr       */
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
		return (ft_cdup('\0'));
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

t_envcpy	*ft_add_new_env(t_shell *shell, char *s)
{
	t_envcpy	*new;

	new = malloc(sizeof(t_envcpy));
	if (!new)
		ft_free_malloc(shell);
	new->name = ft_get_name(s);
	ft_verif_malloc(shell, new->name);
	new->value = ft_get_value_export(s);
	ft_verif_malloc(shell, new->value);
	new->var = ft_strdup(s);
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
	new = ft_add_new_env(shell, s);
	next = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = next;
	next->prev = new;
}

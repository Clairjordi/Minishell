/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:43:38 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/17 14:41:50 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_create_lst_env(t_shell *shell, char **envp)
{
	int			i;
	t_envcpy	*envcpy;
	t_envcpy	*new;

	i = 1;
	envcpy = ft_new_elem_env(shell, envp[0]);
	shell->env->first = envcpy;
	while (envp[i])
	{
		new = ft_new_elem_env(shell, envp[i]);
		new->prev = envcpy;
		envcpy->next = new;
		envcpy = envcpy->next;
		i++;
	}
}

char	*ft_get_name(char *name_env)
{
	int		i;
	char	*name;

	i = 0;
	while (name_env[i] && name_env[i] != '=')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (name_env[i] && name_env[i] != '=')
	{
		name[i] = name_env[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*ft_get_value(char *value_env)
{
	int		i;
	int		len;
	char	*value;

	while (*value_env && *value_env != '=')
		value_env++;
	value_env++;
	len = ft_strlen(value_env);
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	i = 0;
	while (*value_env)
	{
		value[i] = *value_env;
		value_env++;
		i++;
	}
	value[i] = '\0';
	return (value);
}

t_envcpy	*ft_new_elem_env(t_shell *shell, char *str)
{
	t_envcpy	*new;

	new = malloc(sizeof(t_envcpy));
	if (!new)
		ft_free_malloc(shell);
	new->name = ft_get_name(str);
	ft_verif_malloc(shell, new->name);
	new->value = ft_get_value(str);
	ft_verif_malloc(shell, new->value);
	new->var = ft_strdup(str);
	ft_verif_malloc(shell, new->var);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:43:38 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/04 18:59:36 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->built->env[i])
	{
		ft_printf("%s\n", shell->built->env[i]);
		i++;
	}
}

void	ft_recup_env(t_shell *shell)
{
	int			i;
	int			len_double_array;
	t_envcpy	*tmp;

	i = 0;
	len_double_array = 0;
	tmp = shell->env->first;
	while (tmp)
	{
		len_double_array++;
		tmp = tmp->next;
	}
	shell->built->env = ft_calloc(sizeof(char *), (len_double_array + 1));
	if (!shell->built->env)
		ft_free_malloc(shell);
	tmp = shell->env->first;
	while (tmp)
	{
		shell->built->env[i] = ft_strdup(tmp->var);
		if (shell->built->env[i] == NULL)
			ft_free_malloc(shell);
		tmp = tmp->next;
		i++;
	}
	shell->built->env[i] = NULL;
}

char	*ft_get_name(char *name_env)
{
	int		i;
	char 	*name;

	i = 0;
	while (name_env[i] && name_env[i] != '=')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (name_env[i] != '=')
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

t_envcpy	*ft_new_elem_env(char *str)
{
	t_envcpy	*new;

	new = malloc(sizeof(t_envcpy));
	new->name = ft_get_name(str);
	new->value = ft_get_value(str);
	new->var = ft_strdup(str);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

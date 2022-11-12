/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 09:28:03 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/12 19:03:48 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_export_lst(t_envcpy *export)
{
	t_envcpy	*tmp;
	t_envcpy	*buf;

	tmp = export;
	while (tmp)
	{
		buf = tmp->next;
		if (tmp->name != NULL)
			free(tmp->name);
		if (tmp->value != NULL)
			free(tmp->value);
		if (tmp->var != NULL)
			free(tmp->var);
		free(tmp);
		tmp = buf;
	}
	export = NULL;
}

void	ft_write_export(t_envcpy *env)
{
	t_envcpy	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->name, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd(tmp->value, 1);
		ft_putendl_fd("\"", 1);
		tmp = tmp->next;
	}
	ft_free_export_lst(env);
	g_g.status = 0;
}

t_envcpy	*ft_cpy_env(t_envcpy *env_lst)
{
	t_envcpy	*new;

	new = malloc(sizeof(t_envcpy));
	if (!new)
		return (NULL);
	new->name = ft_strdup(env_lst->name);
	new->value = ft_strdup(env_lst->value);
	new->var = ft_strdup(env_lst->var);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_envcpy	*ft_create_export_lst(t_shell *shell)
{
	t_envcpy	*export;
	t_envcpy	*tmp;
	t_envcpy	*add;
	t_envcpy	*cpy;

	export = ft_cpy_env(shell->env->first);
	tmp = export;
	cpy = shell->env->first;
	cpy = cpy->next;
	while (cpy)
	{
		add = ft_cpy_env(cpy);
		tmp->next = add;
		add->prev = tmp;
		tmp = add;
		cpy = cpy->next;
	}
	return (export);
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

t_envcpy	*ft_sorted_by_ascii(t_envcpy *export)
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
	return (sorted);
}

int	ft_name_var(char *s)
{
	int	i;

	i = 0;
	if (ft_isalpha(s[0]) == 1 || s[0] == '_')
		i++;
	while (s[i])
	{
		while (ft_isalnum(s[i]) == 1)
			i++;
		if (s[i] == '=')
			return (1);
		if (s[i] == '\0')
			return (2);
		if (s[i] == '+' && s[i + 1] == '=')
			return (3);
		else
			break ;
	}
	return (0);
}

int	ft_check_name_var(char *s)
{
	int	check;

	check = 0;
	if (ft_isalpha(s[0]) == 0 && s[0] != '_')
	{
		ft_putendl_fd("bash : unset: not a valid identifier", 2);
		g_g.status = 1;
		return (check);
	}
	check = ft_name_var(s);
	if (check == 1)
		return (1);
	else if (check == 2)
		return (2);
	else if (check == 3)
		return (3);
	return (check);
}

char	*ft_get_value_export(char *s)
{
	int		i;
	int		len;
	char	*value;

	if (s == NULL)
		return (NULL);
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

t_envcpy	*ft_add_new_elem(char *s)
{
	t_envcpy	*new;

	new = malloc(sizeof(t_envcpy));
	if (!new)
		return (NULL);
	new->name = ft_get_name(s);
	new->value = ft_get_value_export(s);
	new->var = s;
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
	new = ft_add_new_elem(s);
	next = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = next;
	next->prev = new;
}

void	ft_add_export(t_envcpy *env, char *s)
{
	t_envcpy	*new;
	t_envcpy	*tmp;
	t_envcpy	*next;

	tmp = env;
	new = ft_add_new_elem(s);
	next = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = next;
	next->prev = new;
}

void	ft_export(t_shell *shell)
{
	int			i;
	int			check;
	t_envcpy	*sorted;
	t_envcpy	*export;

	i = 1;
	check = 0;
	export = ft_create_export_lst(shell);
	sorted = ft_sorted_by_ascii(export);
	if (ft_size_tab(shell->exec->builtins) == 1)
	{
		ft_write_export(sorted);
		return ;
	}
	while (shell->exec->builtins[i])
	{
		check = ft_check_name_var(shell->exec->builtins[i]);
		if (check == 1)
		{
			ft_add_var_env(shell->env->first, shell->exec->builtins[i]);
			ft_add_export(export, shell->exec->builtins[i]);
		}
		else if (check == 2)
			ft_add_export(export, shell->exec->builtins[i]);
		/* else if (check == 3) */
		/* { */
		/* 	ft_append_var(shell->env->first, shell->exec->builtins[i]); */
		/* 	ft_append_var(export, shell->exec->builtins[i]); */
		/* } */
		else
			break ;
		i++;
	}
	g_g.status = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getexport_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:07:49 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/17 16:20:20 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_name_env(t_shell *shell, char *s)
{
	int		i;
	char	*name;

	i = 0;
	while ((s[i] && s[i] != '+') && (s[i] && s[i] != '='))
		i++;
	if ((s[i] == '+' || s[i] == '=') && s[i + 1] != '\0')
	{
		i++;
		if (s[i] == '=')
			i++;
	}
	else if (s[i] != '+' && s[i] != '=' && s[i] != '\0')
		return (NULL);
	name = ft_create_name_env(s, i);
	ft_verif_malloc(shell, name);
	return (name);
}

char	*ft_get_name_export(char *s)
{
	int		i;
	char	*name;

	i = 0;
	while (s[i] && s[i] != '+')
		i++;
	if (s[i] != '+')
		return (NULL);
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (s[i] != '+')
	{
		name[i] = s[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

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

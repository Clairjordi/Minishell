/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:57:03 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/17 16:48:02 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_write_export_bis(t_shell *shell, t_envcpy *env)
{
	t_envcpy	*tmp;
	int			fd;

	tmp = env;
	fd = shell->exec->outfile;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(tmp->name, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd("\"", fd);
		if (tmp->value != NULL)
			ft_putstr_fd(tmp->value, fd);
		ft_putendl_fd("\"", fd);
		tmp = tmp->next;
	}
}

void	ft_write_export(t_shell *shell, t_envcpy *env)
{
	t_envcpy	*tmp;

	tmp = env;
	if (shell->exec->outfile > 2)
		ft_write_export_bis(shell, env);
	else
	{
		while (tmp)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
			if (tmp->value != NULL)
				ft_putstr_fd(tmp->value, 1);
			ft_putendl_fd("\"", 1);
			tmp = tmp->next;
		}
	}
	g_minishell.status = 0;
}

char	*ft_create_value_export(char *s)
{
	int		len;
	char	*value;
	int		i;

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

char	*ft_create_name_env(char *s, int i)
{
	char	*name;

	name = NULL;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '+' && s[i] != '=')
	{
		name[i] = s[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:27:26 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/11 14:59:10 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_valid_name(char *s)
{
	int	i;

	i = 0;
	if (ft_isalpha(s[0]) == 1 || s[0] == '_')
		i++;
	while (s[i])
	{
		while (ft_isalnum(s[i]) == 1/* && s[i + 1] != '\0'*/)
			i++;
		if (s[i] == '\0')
			return (1);
		else
			break ;
	}
	return (0);
}

int	ft_check_valid_name(char *s)
{
	if (ft_isalpha(s[0]) == 0 && s[0] != '_')
	{
		ft_putendl_fd("bash: unset: not a valid identifier", 2);
		g_g.status = 1;
	}
	else if (ft_valid_name(s) == 1)
		return (1);
	return (0);
}

t_envcpy	*ft_check_name_envcpy(t_shell *shell, char *s)
{
	t_envcpy *tmp;

	tmp = shell->env->first;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, s) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_remove(t_shell *shell, char *s)
{
	t_envcpy	*tmp;
	t_envcpy	*prev;
	t_envcpy	*next;

	tmp = ft_check_name_envcpy(shell, s);
	if (tmp == NULL)
		return ;
	else
	{
		prev = tmp->prev;
		next = tmp->next;
		prev->next = next;
		next->prev = prev;
		free(tmp->name);
		free(tmp->value);
		free(tmp->var);
		free(tmp);
	}
}

void	ft_unset(t_shell *shell)
{
	int	i;

	i = 1;
	if (shell->exec->builtins[i] == NULL)
		return ;
	if (shell->exec->builtins[i][0] == '-')
	{
		ft_putendl_fd("bash: unset: invalid option", 2);
		g_g.status = 2;
		return ;
	}
	while (shell->exec->builtins[i])
	{
		if (ft_check_valid_name(shell->exec->builtins[i]) == 1)
			ft_remove(shell, shell->exec->builtins[i]);
		i++;
	}
	g_g.status = 0;
}

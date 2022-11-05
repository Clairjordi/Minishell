/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:47:52 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/04 19:55:41 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

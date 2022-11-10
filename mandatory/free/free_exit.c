/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:36:20 by clorcery          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/10 10:17:17 by clorcery         ###   ########.fr       */
=======
/*   Updated: 2022/11/10 10:17:30 by mcloarec         ###   ########.fr       */
>>>>>>> df61538a6c455b738f6575f25c96ecb6fbdbfa1e
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_built(t_shell *shell)
{
	if (shell->built->env != NULL)
		shell->built->env = ft_free_tab_char(shell->built->env);
	free(shell->built);
	shell->built = NULL;
}

void	ft_free_envcpy(t_shell *shell)
{
	t_envcpy	*tmp;
	t_envcpy	*buf;

	if (shell->env->first == NULL)
		return ;
	tmp = shell->env->first;
	while (tmp != NULL)
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
	shell->env->first = NULL;
	free(shell->env);
}

void	ft_free_last_built(t_shell *shell)
{
	ft_free_built(shell);
	ft_free_envcpy(shell);
}

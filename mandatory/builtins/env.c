/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:47:52 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/09 15:33:39 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_recup_env(char **envp, t_shell *shell)
{
	int	i;
	int	len_double_array;

	i = 0;
	len_double_array = 0;
	while (envp[len_double_array] != NULL)
		len_double_array++;
	shell->copy_envp = ft_calloc(sizeof(char *), (len_double_array + 1));
	if (!shell->copy_envp)
		ft_error("Malloc");
	while (envp[i] != NULL)
	{
		shell->copy_envp[i] = ft_strdup(envp[i]);
		if (shell->copy_envp[i] == NULL)
		{
			ft_free_shell(shell);
			ft_error("Malloc");
		}
		i++;
	}
	shell->copy_envp[i] = NULL;
}

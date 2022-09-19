/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:47:52 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/19 11:56:15 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			ft_free_malloc(shell);
		i++;
	}
	shell->copy_envp[i] = NULL;
}

void	ft_add_envp(char **envp, t_shell *shell)
{
	//parametre : ajout de la cmd et peut du nombre de case a ajouter (?)
	if (!shell->copy_envp)
		ft_recup_env(envp, shell);
	if (shell->test_add_env != NULL)
		shell->copy_envp = ft_realloc_tab_char(shell, shell->copy_envp);
	/*
	//verification si la commande n'est pas NULL puis ajout d'une case
	//(gerer quand il y en a plusieurs car l'on peut creer plusieurs variables a la suite)
	if (\cmd/ != NULL)
		shell->copy_envp = ft_realloc_tab_char(shell, shell->copy_envp);
		//peut etre creer une boucle
	*/
}

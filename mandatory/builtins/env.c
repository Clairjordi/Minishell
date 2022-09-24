/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:47:52 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/24 14:50:28 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_recup_env(char **envp, t_shell *shell, t_cmds *cmds)
{
	int	i;
	int	len_double_array;

	i = 0;
	len_double_array = 0;
	while (envp[len_double_array] != NULL)
		len_double_array++;
	shell->copy_envp = ft_calloc(sizeof(char *), (len_double_array + 1));
	if (!shell->copy_envp)
		ft_free_malloc(shell, cmds);
	while (envp[i] != NULL)
	{
		shell->copy_envp[i] = ft_strdup(envp[i]);
		if (shell->copy_envp[i] == NULL)
			ft_free_malloc(shell, cmds);
		i++;
	}
	shell->copy_envp[i] = NULL;
}

void	ft_add_envp(char **envp, t_shell *shell, t_cmds *cmds)
{
	//parametre : ajout de la cmd et peut du nombre de case a ajouter (?)
	if (!shell->copy_envp)
		ft_recup_env(envp, shell, cmds);
	/*
	//verification si la commande n'est pas NULL puis ajout d'une case
	//(gerer quand il y en a plusieurs car l'on peut creer plusieurs variables a la suite)
	if (\cmd/ != NULL)
		shell->copy_envp = ft_realloc_tab_char(shell->copy_envp, \cmd/);
		if(!shell->copy_env)
			ft_free_malloc(shell, cmds);
		//peut etre creer une boucle
	*/
}

void	ft_print_envp(char **envp, t_shell *shell, t_cmds *cmds)
{
	int		i;

	i = 0;
	if (!shell->copy_envp)
		ft_recup_env(envp, shell, cmds);
	while (shell->copy_envp[i] != NULL)
	{
		ft_printf("%s\n", shell->copy_envp[i]);
		i++;
	}
}

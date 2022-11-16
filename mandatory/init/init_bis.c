/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:42:52 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/16 16:42:00 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_envcpy(t_shell *shell)
{
	shell->env = malloc(sizeof(t_env));
	shell->env->first = NULL;
	shell->env->head = NULL;
}

void	ft_init_built(t_shell *shell)
{
	shell->built->env = NULL;
}

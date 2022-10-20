/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:50:01 by clorcery          #+#    #+#             */
/*   Updated: 2022/10/20 18:50:35 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_malloc(t_shell *shell)
{
	ft_free_shell(shell);
	ft_free_cmds(shell);
	ft_error("Malloc error");
}

void	*ft_free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

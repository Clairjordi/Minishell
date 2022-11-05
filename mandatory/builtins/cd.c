/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:57:11 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/04 15:37:08 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_built_cd(char *path)
{
	if (chdir(path) == -1)
		perror("chdir");
}

void	ft_execute_built(t_shell *shell)
{

}

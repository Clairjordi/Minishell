/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:47:13 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/24 18:47:50 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_verif_pipe(char *s)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	if (s[i] == '|')
	{
		ft_putendl_fd("Wrong pipes syntax", 2);
		return (-1);
	}
	while (s[i])
	{
		if (s[i] == '|')
			pipe++;
		if (s[i + 1] == '\0' && s[i] == '|')
		{
			ft_putendl_fd("Wrong pipes syntax", 2);
			return (-1);
		}
		i++;
	}
	return (pipe);
}

int	ft_check_pipe(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (shell->tab_cmd[i] != NULL)
	{
		j = 0;
		while (shell->tab_cmd[i][j])
		{
			if (shell->tab_cmd[i][j] == '|' && shell->tab_cmd[i][j + 1] == '|')
			{
				ft_free(shell, "Wrong pipes syntax");
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

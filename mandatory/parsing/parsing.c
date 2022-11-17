/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:01:37 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/17 17:14:58 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_verif_if_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
	{
		if (str[i + 1] == '\0')
			return (ERROR);
		i++;
	}
	if (str[0] == '\0')
		return (ERROR);
	return (0);
}

int	ft_verif_parsing(char *str)
{
	if (ft_verif_if_str(str) == ERROR)
		return (ERROR);
	if (ft_count_quote(str) == ERROR)
		return (ERROR);
	if (ft_verif_pipe(str) == ERROR)
		return (ERROR);
	if (ft_verif_redirect(str) == ERROR)
		return (ERROR);
	return (0);
}

void	ft_parsing(char *str, t_shell *shell)
{
	if (ft_verif_parsing(str) == ERROR)
	{
		ft_free(shell, NULL);
		return ;
	}
	shell->tab_cmd = ft_split_pipes(str, '|');
	if (shell->tab_cmd == NULL)
		ft_free_malloc(shell);
	if (ft_check_space_pipe(shell) == ERROR)
	{
		ft_free(shell, NULL);
		return ;
	}
	ft_create_lst(shell);
	ft_replace_value(shell);
	ft_recup_env(shell);
	ft_minishell(shell);
	ft_free(shell, NULL);
	if (access(".heredoc", F_OK) == 0)
		unlink(".heredoc");
}

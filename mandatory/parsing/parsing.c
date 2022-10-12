/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:01:37 by clorcery          #+#    #+#             */
/*   Updated: 2022/10/12 17:15:49 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_verif_if_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\"')
	{
		if (str[i + 1] == '\"' && str[i + 2] == '\0')
		{
			ft_putendl_fd("Command not found", 2);
			return (-1);
		}
	}
	else if (str[i] == '\'')
	{
		if (str[i + 1] == '\'' && str[i + 2] == '\0')
		{
			ft_putendl_fd("Command not found", 2);
			return (-1);
		}
	}
	return (0);
}

int	ft_verif_parsing(char *str, t_shell *shell)
{
	if (ft_verif_if_str(str) == -1)
		return (-1);
	if (ft_count_quote(str) == -1)
		return (-1);
	if (ft_verif_pipe(shell, str) == -1)
		return (-1);
	if (ft_verif_redirect(str) == -1)
		return (-1);
	return (0);
}

int	ft_parsing_bis(t_shell *shell)
{
	if (ft_replace_value(shell) == -1)
		return (-1);
	return (0);
}

void	ft_parsing(char *str, t_shell *shell)
{
	if (ft_verif_parsing(str, shell) == -1)
		return ;
	shell->tab_cmd = ft_split_pipes(str, '|');
	if (shell->tab_cmd == NULL)
		ft_free_malloc(shell);
	ft_create_lst(shell);
	if (ft_parsing_bis(shell) == -1)
		return ;
	ft_print_test(shell); //A SUPPR
	ft_free(shell, NULL);
}

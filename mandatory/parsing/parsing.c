/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:01:37 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/26 15:11:29 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_redirection(t_shell *shell)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (shell->tab_cmd[i])
	{
		if ((shell->tab_cmd[i][0] == '<' && shell->tab_cmd[i][1] == '>')
				|| (shell->tab_cmd[i][0] == '>' && shell->tab_cmd[i][1] == '<'))
		{
			ft_free(shell, "Wrong redirection syntax");
			return (-1);
		}
		else if (shell->tab_cmd[i][0] == '<' || shell->tab_cmd[i][0] == '>')
		{
			size = ft_strlen(shell->tab_cmd[i]);
			if (size > 2)
			{
				ft_free(shell, "Wrong redirection syntax");
				return (-1);
			}
		}
		i++;
	}
	return (size);
}

int	ft_verif_parsing(t_shell *shell)
{
	if (ft_check_pipe(shell) == -1)
		return (-1);
	if (ft_check_redirection(shell) == -1)
		return (-1);
	return (0);
}

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

void	ft_parsing(char *str, t_shell *shell, char **envp)
{
	(void) envp;
	if (ft_verif_if_str(str) == -1)
		return ;
	if (ft_count_quote(str) == -1)
		return ;
	if (ft_verif_pipe(str) == -1)
		return ;
	else
	{
		shell->tab_cmd = ft_split_shell(str);
		if (shell->tab_cmd == NULL)
			ft_free_malloc(shell);
	}
	if (ft_verif_parsing(shell) == -1) //free fait dans les fonctions
		return ;
	ft_create_linked_lst(shell);
	ft_print_test(shell); //A SUPPR
	ft_free(shell, NULL);
}

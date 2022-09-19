/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:33:44 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/19 18:31:15 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_shell(t_shell *shell, t_cmds *cmds)
{
	shell->copy_envp = NULL;
	shell->copy_export = NULL;
	shell->test_add_env = NULL; //A SUPPR
	cmds->prev = NULL;
	cmds->next = NULL;
	cmds->cmd = NULL;
	cmds->opt = NULL;
	cmds->infile = -1;
	cmds->outfile = -1;
	cmds->heredoc = '\0';
}

void	ft_init_prompt(t_shell *shell, t_cmds *cmds)
{
	char	*str;

	while (1)
	{
		str = readline ("$>");
		if (!str || !ft_strncmp("exit", str, 4))
		{
			ft_putstr_fd("exit\n", 1); // manque des frees
			exit (0);
		}
		if (str)
		{
			add_history(str);
			ft_parsing(str, shell);
		}
		free(str);
	}
}

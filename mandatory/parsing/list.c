/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:45:51 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/24 23:00:02 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_create_linked_lst(t_shell *shell)
{
	int		i;
	//int		pipe;
	t_cmds	*new;
	//char	*tmp;

	i = 1;
//	pipe = 0;
	shell->arg = ft_lstnew_cmd(shell->tab_cmd[0]);
//	tmp = shell->tab_cmd[0];
	while (shell->tab_cmd[i] != NULL)
	{
		new = ft_lstnew_cmd(shell->tab_cmd[i]);
		ft_lstaddback_cmd(&shell->arg, new);
		i++;
	}
	//EN ATTENTE - creer un seul element entre les pipes
	/* while (shell->tab_cmd[i] != NULL) */
	/* { */
	/* 	#<{(| if (ft_strcmp(shell->tab_cmd[i], "|") == 0) |)}># */
	/* 	#<{(| { |)}># */
	/* 	#<{(| 	tmp = ft_strcat(shell->tab_cmd[i], shell->tab_cmd[i + 1])  |)}># */
	/* 	#<{(| } |)}># */
	/*  */
    /*  */
	/* 	if (pipe == 0 && ft_strcmp(shell->tab_cmd[i], "|") != 0) */
	/* 		tmp = ft_strcat(tmp, shell->tab_cmd[i]); */
	/* 	else if (pipe != 0 && ft_strcmp(shell->tab_cmd[i], "|") != 0) */
	/* 	{ */
	/* 		if (tmp == NULL) */
	/* 			tmp = shell->tab_cmd[i]; */
	/* 		else  */
	/* 			tmp = ft_strcat(tmp, shell->tab_cmd[i]); */
	/* 	} */
	/* 	if (pipe == 0 && (ft_strcmp(shell->tab_cmd[i], "|") == 0 || shell->tab_cmd[i + 1] == NULL)) */
	/* 	{ */
	/* 		pipe++; */
	/* 		free(shell->arg->value); */
	/* 		shell->arg->value = tmp; */
	/* 		if (tmp != NULL) */
	/* 		{ */
	/* 			free(tmp); */
	/* 			tmp = NULL; */
	/* 		} */
	/* 	} */
	/* 	else if (pipe != 0 && (ft_strcmp(shell->tab_cmd[i], "|") == 0 || shell->tab_cmd[i + 1] == NULL)) */
	/* 	{ */
	/* 		new = ft_lstnew_cmd(tmp#<{(|shell->tab_cmd[i]|)}>#); */
	/* 		ft_lstaddback_cmd(&shell->arg, new); */
	/* 		if (tmp != NULL) */
	/* 		{ */
	/* 			free(tmp); */
	/* 			tmp = NULL; */
	/* 		} */
	/* 	} */
	/* 	i++; */
	/* } */
}

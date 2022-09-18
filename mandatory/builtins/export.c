/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:48:59 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/17 19:26:34 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_sort_export(t_shell *shell)
{
	int		i;
	char	*tmp;
	int		j;

	i = 0;
	while (shell->copy_export[i] != NULL)
	{
		j = i + 1;
		while (shell->copy_export[j] != NULL)
		{
			if (ft_strncmp(shell->copy_export[i], shell->copy_export[j], 13) > 0)
			{
				tmp = shell->copy_export[j];
				shell->copy_export[j] = shell->copy_export[i];
				shell->copy_export[i] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	ft_len_va(char *var, int start, char c)
{
	int	i;

	i = start;
	while (var[i])
	{
		if (var[i] == c)
		{
			i++;
			return (i);
		}
		i++;
	}
	i++;
	return (i);
}

void	ft_export(char **envp, t_shell *shell)
{
	int		i;
	int		len_double_array;
	char	*tab_var;
	char	*tab_val;
	size_t		size;

	i = 0;
	len_double_array = 0;
	while (envp[len_double_array] != NULL)
		len_double_array++;
	shell->copy_export = ft_calloc(sizeof(char *), (len_double_array + 1));
	if (!shell->copy_export)
		ft_free_malloc(shell);
	while (envp[i] != NULL) 
	{
		size = ft_len_va(envp[i], 0, '=');
		tab_var = ft_substr(envp[i], 0, size);
		if (tab_var == NULL)
			ft_free_malloc(shell);
		tab_val = ft_substr(envp[i], size, ft_len_va(envp[i], size, '\0'));
		if (tab_val == NULL)
			ft_free_malloc(shell);
		tab_val = ft_strjoin_free("\"", tab_val, '2');
		tab_val = ft_strjoin_free(tab_val, "\"", '1');
		shell->copy_export[i] = ft_strjoin_free(tab_var, tab_val, 3);
		free(tab_var);
		free(tab_val);
		i++;
	}
	shell->copy_export[i] = NULL;
	ft_sort_export(shell);
	i = 0;
	while (shell->copy_export[i] != NULL)
	{
		shell->copy_export[i] = ft_strjoin_free("declare -x ",
				shell->copy_export[i], '2');
		if (shell->copy_export[i] == NULL)
			ft_free_malloc(shell);
		i++;
	}
}

/*  */
/* void	ft_export(char **envp, t_shell *shell) */
/* { */
/* 	int	i; */
/*  */
/* 	i = 0; */
/* 	ft_recup_env(envp, shell); */
/* 	shell->copy_export = shell->copy_envp; */
/* 	ft_sort_export(shell); */
/* 	ft_add_quotes(shell); */
/* 	while (shell->copy_export[i] != NULL) */
/* 	{ */
/* 		shell->copy_export[i] = ft_strjoin_free("declare -x ", */
/* 				shell->copy_export[i], '2'); */
/* 		if (shell->copy_export[i] == NULL) */
/* 			ft_free_malloc(shell); */
/* 		i++; */
/* 	} */
/* } */

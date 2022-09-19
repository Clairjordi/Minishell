/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:48:59 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/19 12:04:47 by clorcery         ###   ########.fr       */
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
			if (ft_strncmp(shell->copy_export[i],
					shell->copy_export[j], 13) > 0)
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
	if (var[i] == '\0')
		i++;
	return (i);
}

static char	*annoying_malloc(char *tab_val, t_shell *shell)
{
	tab_val = ft_strjoin_free("\"", tab_val, '2');
	if (tab_val == NULL)
		ft_free_malloc(shell);
	tab_val = ft_strjoin_free(tab_val, "\"", '1');
	if (tab_val == NULL)
		ft_free_malloc(shell);
	return (tab_val);
}

void	ft_create_copy_export(t_shell *shell)
{
	int		i;
	char	*tab_var;
	char	*tab_val;
	int		size;

	i = 0;
	while (shell->copy_envp[i] != NULL)
	{
		size = ft_len_va(shell->copy_envp[i], 0, '=');
		tab_var = ft_substr(shell->copy_envp[i], 0, size);
		if (tab_var == NULL)
			ft_free_malloc(shell);
		tab_val = ft_substr(shell->copy_envp[i], size,
				ft_len_va(shell->copy_envp[i], size, '\0'));
		if (tab_val == NULL)
			ft_free_malloc(shell);
		tab_val = malloc_qui_fait_suer(tab_val, shell);
		shell->copy_export[i] = ft_strjoin_free(tab_var, tab_val, 3);
		free(tab_var);
		free(tab_val);
		i++;
	}
	shell->copy_export[i] = NULL;
}

void	ft_export(char **envp, t_shell *shell)
{
	int		i;
	int		len_double_array;

	i = 0;
	len_double_array = 0;
	if (!shell->copy_envp)
		ft_recup_env(envp, shell);
	while (shell->copy_envp[len_double_array] != NULL)
		len_double_array++;
	shell->copy_export = ft_calloc(sizeof(char *), (len_double_array + 1));
	if (!shell->copy_export)
		ft_free_malloc(shell);
	ft_create_copy_export(shell);
	ft_sort_export(shell);
	while (shell->copy_export[i] != NULL)
	{
		shell->copy_export[i] = ft_strjoin_free("declare -x ",
				shell->copy_export[i], '2');
		if (shell->copy_export[i] == NULL)
			ft_free_malloc(shell);
		i++;
	}
}

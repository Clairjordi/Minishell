/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:57:11 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/14 18:33:52 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//MANQUE REPLACE VALUE DANS EXPORT

/* static void	ft_replace_value_pwd_export(t_shell *shell) */
/* { */
/* 	char		*name_pwd; */
/* 	char		*name_old_pwd; */
/* 	t_?	*lst_pwd; */
/* 	t_?	*lst_old_pwd; */
/*  */
/* } */

static void	ft_replace_value_pwd_env(t_shell *shell)
{
	char		*pwd;
	char		*name_pwd;
	char		*name_old_pwd;
	t_envcpy	*lst_pwd;
	t_envcpy	*lst_old_pwd;

	name_pwd = "PWD";
	name_old_pwd = "OLDPWD";
	lst_pwd = ft_check_name_envcpy(shell, name_pwd);
	lst_old_pwd = ft_check_name_envcpy(shell, name_old_pwd);
	if (lst_pwd != NULL && lst_old_pwd != NULL)
	{
		free(lst_old_pwd->value);
		lst_old_pwd->value = ft_strdup(lst_pwd->value);
		pwd = getcwd(NULL, 0);
		free(lst_pwd->value);
		lst_pwd->value = ft_strdup(pwd);
		free(lst_old_pwd->var);
		lst_old_pwd->var = ft_strjoin(lst_old_pwd->name, lst_old_pwd->value);
		free(lst_pwd->var);
		lst_pwd->var = ft_strjoin(lst_pwd->name, lst_pwd->value);
		free(pwd);
	}
}

void	ft_cd(t_shell *shell, char **tab)
{
	(void) shell;
	if (tab[1] == NULL)
	{
		ft_putendl_fd("bash: cd: too few argument", 2);
		g_minishell.status = 1;
		return ;
	}
	if (tab[2] != NULL)
	{
		ft_putendl_fd("bash: cd: too many arguments", 2);
		g_minishell.status = 1;
		return ;
	}	
	if (chdir(tab[1]) == -1)
	{
		perror("chdir");
		g_minishell.status = 1;
		return ;
	}
	ft_replace_value_pwd_env(shell);
	//ft_replace_value_pwd_export(shell);
	g_minishell.status = 0;
}

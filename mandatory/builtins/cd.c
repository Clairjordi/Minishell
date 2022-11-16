/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:57:11 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/16 18:26:52 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_replace_value_pwd_export(t_shell *shell,
		t_envcpy *env_pwd, t_envcpy *env_oldpwd)
{
	t_envcpy	*exp_pwd;
	t_envcpy	*exp_oldpwd;

	exp_pwd = ft_check_name_envcpy(shell->env->head, "PWD");
	exp_oldpwd = ft_check_name_envcpy(shell->env->head, "OLDPWD");
	if (exp_pwd != NULL && exp_oldpwd != NULL)
	{
		free(exp_oldpwd->value);
		exp_oldpwd->value = ft_strdup(env_oldpwd->value);
		ft_verif_malloc(shell, exp_oldpwd->value);
		free(exp_pwd->value);
		exp_pwd->value = ft_strdup(env_pwd->value);
		ft_verif_malloc(shell, exp_pwd->value);
		free(exp_oldpwd->var);
		exp_oldpwd->var = ft_strdup(env_oldpwd->var);
		ft_verif_malloc(shell, exp_oldpwd->var);
		free(exp_pwd->var);
		exp_pwd->var = ft_strdup(env_pwd->var);
		ft_verif_malloc(shell, exp_pwd->var);
	}
}

static void	ft_replace_value_pwd_env(t_shell *shell)
{
	char		*pwd;
	t_envcpy	*env_pwd;
	t_envcpy	*env_oldpwd;

	env_pwd = ft_check_name_envcpy(shell->env->first, "PWD");
	env_oldpwd = ft_check_name_envcpy(shell->env->first, "OLDPWD");
	if (env_pwd != NULL && env_oldpwd != NULL)
	{
		free(env_oldpwd->value);
		env_oldpwd->value = ft_strdup(env_pwd->value);
		ft_verif_malloc(shell, env_oldpwd->value);
		pwd = getcwd(NULL, 0);
		free(env_pwd->value);
		env_pwd->value = ft_strdup(pwd);
		ft_verif_malloc(shell, env_pwd->value);
		free(env_oldpwd->var);
		env_oldpwd->var = ft_strjoin(env_oldpwd->name, env_oldpwd->value);
		ft_verif_malloc(shell, env_oldpwd->var);
		free(env_pwd->var);
		env_pwd->var = ft_strjoin(env_pwd->name, env_pwd->value);
		ft_verif_malloc(shell, env_pwd->var);
		free(pwd);
		ft_replace_value_pwd_export(shell, env_pwd, env_oldpwd);
	}
}

void	ft_cd(t_shell *shell, char **tab)
{
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
	g_minishell.status = 0;
}

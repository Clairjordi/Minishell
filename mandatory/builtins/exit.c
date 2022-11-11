/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:15:09 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/11 17:32:57 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_arg_exit(char *arg_exit)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	if (arg_exit[0] == '+' || arg_exit[0] == '-')
		i++;
	if (arg_exit[0] == '\'' || arg_exit[0] == '\"')
	{
		quote = arg_exit[0];
		i++;
	}
	while (arg_exit[i])
	{
		if (arg_exit[i + 1] == '\0' && arg_exit[i] == quote)
			break ;
		if (ft_isdigit(arg_exit[i]) == 0)
		{
			ft_putendl_fd("numeric argument required", 2);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	ft_check_exit_is_valid(char *str)
{
	int	i;
	int	space;

	space = 0;
	i = 0;
	if (str[4] != ' ' && str[4] != '\0')
		return (FALSE);
	if (str[4] == ' ')
	{
		while (str[i])
		{
			if (str[i] == ' ')
				space++;
			if (space > 1)
				return (FALSE);
			i++;
		}
	}
	return (TRUE);
}

int	ft_exit(t_shell *shell, char *str)
{
	char	*arg;
	int		size;

	(void) shell;
	size = ft_strlen(str);
	if (ft_strncmp("exit", str, 4) == 0)
	{
		if (ft_check_exit_is_valid(str) == FALSE)
			return (FALSE);
		if (str[4] != '\0')
		{
			arg = ft_substr(str, 5, (size - 5));
			if (arg == NULL)
				ft_free_malloc(shell);
			if (ft_check_arg_exit(arg) == FALSE)
				g_g.status = 2;
			else
				g_g.status = ft_atoi(arg);
			free(arg);
		}
		return (TRUE);
	}
	return (FALSE);
}

void	ft_exit_fork(char **built)
{
	int	size;

	size = 0;
	size = ft_size_tab(built);
	if (built[1] == NULL)
		return ;
	if (size > 2)
	{
		ft_putendl_fd("exit", 1);
		ft_putendl_fd("too many arguments", 2);
		g_g.status = 1;
		return ;
	}	
	if (ft_check_arg_exit(built[1]) == FALSE)
	{
		g_g.status = 2;
		return ;
	}
	g_g.status = ft_atoi(built[1]);
}

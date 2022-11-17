/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:57:03 by mcloarec          #+#    #+#             */
/*   Updated: 2022/11/17 16:10:43 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_create_value_export(char *s)
{
	int		len;
	char	*value;
	int		i;

	len = ft_strlen(s);
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	i = 0;
	while (*s)
	{
		value[i] = *s;
		s++;
		i++;
	}
	value[i] = '\0';
	return (value);
}

char	*ft_create_name_env(char *s, int i)
{
	char	*name;

	name = NULL;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '+' && s[i] != '=')
	{
		name[i] = s[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

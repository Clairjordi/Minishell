/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:14:02 by clorcery          #+#    #+#             */
/*   Updated: 2022/05/22 17:23:42 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

int	ft_min_int(int *tab, int len)
{
	int	i;
	int	mi_int;

	i = 0;
	mi_int = tab[0];
	while (i < len)
	{
		if (tab[i] < mi_int)
			mi_int = tab[i];
		i++;
	}
	return (mi_int);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prev_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:37:45 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/02 15:53:03 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_prev_int(int *tab, int nb, int len)
{
	int	i;
	int	p_int;

	i = 0;
	p_int = nb;
	while (p_int == nb && i < len)
	{
		if (tab[i] < nb)
			p_int = tab[i];
		i++;
	}
	while (i < len)
	{
		if (tab[i] < nb && tab[i] > p_int)
			p_int = tab[i];
		i++;
	}
	return (p_int);
}

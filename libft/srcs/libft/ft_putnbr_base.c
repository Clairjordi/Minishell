/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:40:24 by clorcery          #+#    #+#             */
/*   Updated: 2022/04/20 13:41:35 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

void	ft_putnbr_base(int nbr, char *base)
{
	int	len;

	len = ft_strlen(base);
	if (base[0] == '\0' || base[1] == '\0')
		ft_putchar_fd('0', 1);
	if (nbr < 0)
	{
		ft_putchar_fd('-', 1);
		ft_putnbr_base(-nbr, base);
	}
	if (nbr >= len)
	{
		ft_putnbr_base(nbr / len, base);
		ft_putnbr_base(nbr % len, base);
	}
	else
		ft_putchar_fd(base[nbr], 1);
}

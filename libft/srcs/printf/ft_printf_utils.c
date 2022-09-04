/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:26:50 by clorcery          #+#    #+#             */
/*   Updated: 2022/04/25 16:48:23 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

int	print_memory(unsigned long n, char *base)
{
	int	count;

	count = 0;
	if (n == 0)
		count += ft_putstr_count("(nil)");
	else
	{
		count += ft_putstr_count("0x");
		count += ft_putnbr_base_p(n, base);
	}
	return (count);
}

int	ft_putnbr_base_p(unsigned long n, char *base)
{
	int				count;
	unsigned long	len_base;

	count = 1;
	len_base = ft_strlen(base);
	if (n >= len_base)
	{
		count += ft_putnbr_base_p(n / len_base, base);
		ft_putnbr_base_p(n % len_base, base);
	}
	else
	{
		ft_putchar_fd(base[n], 1);
		return (count);
	}
	return (count);
}

int	ft_putnbr_base_hexa(unsigned int n, char b)
{
	int				count;
	char			*base;
	unsigned int	len_base;

	if (b == 'X')
		base = "0123456789ABCDEF";
	if (b == 'x')
		base = "0123456789abcdef";
	count = 1;
	len_base = ft_strlen(base);
	if (n >= len_base)
	{
		count += ft_putnbr_base_hexa(n / len_base, b);
		ft_putnbr_base_hexa(n % len_base, b);
	}
	else
	{
		ft_putchar_fd(base[n], 1);
		return (count);
	}
	return (count);
}

int	ft_putnbr_count(int n)
{
	unsigned int	nb;
	int				count;

	count = 1;
	nb = n;
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		nb = n * -1;
		count++;
	}
	if (nb >= 10)
		count += ft_putnbr_count((nb / 10));
	ft_putchar_fd((nb % 10 + '0'), 1);
	return (count);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	int	count;

	count = 1;
	if (n >= 10)
		count += ft_putnbr_count((n / 10));
	ft_putchar_fd((n % 10 + '0'), 1);
	return (count);
}

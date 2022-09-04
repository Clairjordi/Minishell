/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:13:47 by clorcery          #+#    #+#             */
/*   Updated: 2022/04/25 16:48:02 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../all_h.h"

int	ft_putstr_count(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		i += write(1, "(null)", 6);
	else
	{
		while (s[i])
		{
			write(1, &s[i], 1);
			i++;
		}
	}
	return (i);
}

int	ft_putchar_count(char c)
{
	int	count;

	count = write(1, &c, 1);
	return (count);
}

int	print(char type, va_list args)
{
	int	result;

	result = 0;
	if (type == '%')
		result += ft_putchar_count('%');
	else if (type == 'c')
		result += ft_putchar_count(va_arg(args, int));
	else if (type == 's')
		result += ft_putstr_count(va_arg(args, char *));
	else if (type == 'p')
		result += print_memory(va_arg(args, unsigned long), "0123456789abcdef");
	else if (type == 'd' || type == 'i')
		result += ft_putnbr_count(va_arg(args, int));
	else if (type == 'u')
		result += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (type == 'x')
		result += ft_putnbr_base_hexa(va_arg(args, unsigned int), 'x');
	else if (type == 'X')
		result += ft_putnbr_base_hexa(va_arg(args, unsigned int), 'X');
	else
		return (1);
	return (result);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		res;

	i = 0;
	res = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '\0')
			res += print(format[++i], args);
		else
			res += ft_putchar_count((char )format[i]);
		i++;
	}
	va_end(args);
	return (res);
}

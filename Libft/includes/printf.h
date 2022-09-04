/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:00:00 by clorcery          #+#    #+#             */
/*   Updated: 2022/04/25 16:41:03 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

int	ft_printf(const char *format, ...);
int	print(char type, va_list args);
int	ft_putchar_count(char c);
int	ft_putstr_count(char *s);
int	ft_putnbr_base_hexa(unsigned int n, char b);
int	ft_putnbr_base_p(unsigned long n, char *base);
int	ft_putnbr_count(int n);
int	ft_putnbr_unsigned(unsigned int n);
int	print_memory(unsigned long n, char *base);

#endif

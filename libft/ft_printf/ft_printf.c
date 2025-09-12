/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:11:21 by squinn            #+#    #+#             */
/*   Updated: 2025/09/12 15:44:04 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	determine_conversion_type(char letter)
{
	if (letter == '\0')
		return (SINGLE_PERCENT_ERROR);
	if (letter == 'c')
		return (LETTER);
	if (letter == 's')
		return (STRING);
	if (letter == 'p')
		return (POINTER);
	if (letter == 'd' || letter == 'i')
		return (INTEGER);
	if (letter == 'u')
		return (UNSIGNED_INTEGER);
	if (letter == 'x')
		return (LOWER_HEX);
	if (letter == 'X')
		return (UPPER_HEX);
	if (letter == '%')
		return (PERCENT);
	return (UNKNOWN_CONVERSION_TYPE);
}

int	print_by_conversion_type(int type, va_list args, char specifier)
{
	if (type == UNKNOWN_CONVERSION_TYPE)
		return (print_specifier(specifier));
	if (type == LETTER)
		return (ft_putchar(va_arg(args, int)));
	if (type == STRING)
		return (ft_putstr(va_arg(args, char *)));
	if (type == POINTER)
		return (print_address(va_arg(args, void *)));
	if (type == INTEGER)
		return (ft_putnbr(va_arg(args, int)));
	if (type == UNSIGNED_INTEGER)
		return (print_unsigned_decimal(va_arg(args, unsigned int)));
	if (type == LOWER_HEX)
		return (print_hexadecimal(va_arg(args, unsigned int), FALSE));
	if (type == UPPER_HEX)
		return (print_hexadecimal(va_arg(args, unsigned int), TRUE));
	return (ft_putchar('%'));
}

int	ft_vprintf(const char *format, va_list args)
{
	int	result;
	int	type;

	result = 0;
	while (*format)
	{
		if (*format != '%')
		{
			result += ft_putchar(*format);
			format++;
			continue ;
		}
		format++;
		type = determine_conversion_type(*format);
		if (type == SINGLE_PERCENT_ERROR)
			return (-1);
		result += print_by_conversion_type(type, args, *format);
		format++;
	}
	return (result);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		result;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	result = ft_vprintf(format, args);
	va_end(args);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:46:54 by squinn            #+#    #+#             */
/*   Updated: 2025/09/12 17:57:36 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	print_specifier_fd(int fd, char specifier)
{
	int	num_bytes;

	num_bytes = 0;
	num_bytes += ft_putchar_fd('%', fd);
	num_bytes += ft_putchar_fd(specifier, fd);
	if (num_bytes < 0)
		return (0);
	return (num_bytes);
}

int	print_by_conversion_type_fd(int fd, int type, va_list args, char specifier)
{
	if (type == UNKNOWN_CONVERSION_TYPE)
		return (print_specifier_fd(fd, specifier));
	if (type == LETTER)
		return (ft_putchar_fd(va_arg(args, int), fd));
	if (type == STRING)
		return (ft_putstr_fd(va_arg(args, char *), fd));
	if (type == POINTER)
		return (print_address_fd(fd, va_arg(args, void *)));
	if (type == INTEGER)
		return (ft_putnbr_fd(va_arg(args, int), fd));
	if (type == UNSIGNED_INTEGER)
		return (print_unsigned_decimal_fd(fd, va_arg(args, unsigned int)));
	if (type == LOWER_HEX)
		return (print_hexadecimal_fd(fd, va_arg(args, unsigned int), FALSE));
	if (type == UPPER_HEX)
		return (print_hexadecimal_fd(fd, va_arg(args, unsigned int), TRUE));
	return (ft_putchar_fd('%', fd));
}

int	ft_vdprintf(int fd, const char *format, va_list args)
{
	int	result;
	int	type;

	result = 0;
	while (*format)
	{
		if (*format != '%')
		{
			result += ft_putchar_fd(*format, fd);
			format++;
			continue ;
		}
		format++;
		type = determine_conversion_type(*format);
		if (type == SINGLE_PERCENT_ERROR)
			return (-1);
		result += print_by_conversion_type_fd(fd, type, args, *format);
		format++;
	}
	return (result);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		result;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	result = ft_vdprintf(fd, format, args);
	va_end(args);
	return (result);
}

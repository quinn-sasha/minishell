/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:35:08 by squinn            #+#    #+#             */
/*   Updated: 2025/09/12 15:45:46 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putchar(char c)
{
	int	num_bytes;

	num_bytes = write(STDOUT, &c, 1);
	if (num_bytes == -1)
		return (0);
	return (num_bytes);
}

int	print_specifier(char specifier)
{
	int	num_bytes;

	num_bytes = 0;
	num_bytes += ft_putchar('%');
	num_bytes += ft_putchar(specifier);
	if (num_bytes < 0)
		return (0);
	return (num_bytes);
}

int	ft_putstr(const char *str)
{
	int	num_bytes;

	if (str == NULL)
		return (ft_putstr("(null)"));
	num_bytes = 0;
	while (*str)
	{
		num_bytes += ft_putchar(*str);
		str++;
	}
	return (num_bytes);
}

int	ft_putnbr(int num)
{
	int	num_bytes;

	num_bytes = 0;
	if (num == -2147483648)
		return (ft_putstr("-2147483648"));
	if (num < 0)
	{
		num = -num;
		num_bytes += ft_putchar('-');
	}
	if (num < 10)
	{
		num_bytes += ft_putchar(num + '0');
		return (num_bytes);
	}
	num_bytes += ft_putnbr(num / 10);
	num_bytes += ft_putnbr(num % 10);
	return (num_bytes);
}

int	print_unsigned_decimal(unsigned int n)
{
	unsigned long long	num;
	char				*buffer;

	num = (unsigned long long)n;
	buffer = unsigned_itoa(num, 10);
	return (ft_putstr(buffer));
}

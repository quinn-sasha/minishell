/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:57:12 by squinn            #+#    #+#             */
/*   Updated: 2025/09/12 17:26:57 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int num, int fd)
{
	int	num_bytes;

	num_bytes = 0;
	if (num == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	if (num < 0)
	{
		num = -num;
		num_bytes += ft_putchar_fd('-', fd);
	}
	if (num < 10)
	{
		num_bytes += ft_putchar_fd(num + '0', fd);
		return (num_bytes);
	}
	num_bytes += ft_putnbr_fd(num / 10, fd);
	num_bytes += ft_putnbr_fd(num % 10, fd);
	return (num_bytes);
}

/*
#include <stdio.h>

int	main(void) {
	ft_putnbr_fd(-2147483648, 1);
	printf("\n");
	ft_putnbr_fd(-2147483648, 1);
	printf("\n");
	ft_putnbr_fd(0, 1);
}
*/

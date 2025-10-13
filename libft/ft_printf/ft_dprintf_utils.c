/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:46:48 by squinn            #+#    #+#             */
/*   Updated: 2025/09/12 17:46:49 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	print_address_fd(int fd, const void *address)
{
	char				*buffer;
	unsigned long long	num;
	int					num_bytes;

	num = (unsigned long long)address;
	buffer = unsigned_itoa(num, 16);
	if (ft_strncmp(buffer, "0", 1) == 0)
		return (ft_putstr_fd("(nil)", fd));
	num_bytes = 0;
	num_bytes += ft_putstr_fd("0x", fd);
	num_bytes += ft_putstr_fd(buffer, fd);
	return (num_bytes);
}

int	print_unsigned_decimal_fd(int fd, unsigned int n)
{
	unsigned long long	num;
	char				*buffer;

	num = (unsigned long long)n;
	buffer = unsigned_itoa(num, 10);
	return (ft_putstr_fd(buffer, fd));
}

int	print_hexadecimal_fd(int fd, unsigned int n, int is_upper)
{
	unsigned long long	num;
	char				*buffer;
	int					i;

	num = (unsigned long long)n;
	buffer = unsigned_itoa(num, 16);
	if (is_upper)
	{
		i = 0;
		while (buffer[i])
		{
			buffer[i] = (char)ft_toupper(buffer[i]);
			i++;
		}
	}
	return (ft_putstr_fd(buffer, fd));
}

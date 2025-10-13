/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:41:14 by squinn            #+#    #+#             */
/*   Updated: 2025/09/12 15:45:03 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	print_address(const void *address)
{
	char				*buffer;
	unsigned long long	num;
	int					num_bytes;

	num = (unsigned long long)address;
	buffer = unsigned_itoa(num, 16);
	if (ft_strncmp(buffer, "0", 1) == 0)
		return (ft_putstr("(nil)"));
	num_bytes = 0;
	num_bytes += ft_putstr("0x");
	num_bytes += ft_putstr(buffer);
	return (num_bytes);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xclose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:27:39 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/07 16:30:00 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	xclose(int fd)
{
	int	ret;

	if (fd < 0)
		return (-1);
	ret = close(fd);
	if (ret < 0)
		fatal_error("xclose");
	return (ret);
}

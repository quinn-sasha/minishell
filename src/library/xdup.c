/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xdup.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:06:42 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/06 20:11:19 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	xdup(int oldfd)
{
	int	fd;

	fd = dup(oldfd);
	if (fd < 0)
		fatal_error("xdup");
	return (fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xdup2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:06:49 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/06 20:10:04 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	xdup2(int oldfd, int newfd)
{
	int	fd;

	fd = dup2(oldfd, newfd);
	if (fd < 0)
		fatal_error("xdup2");
	return (fd);
}

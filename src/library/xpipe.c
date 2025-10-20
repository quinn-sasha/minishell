/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpipe.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:27:39 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/14 14:35:25 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	xpipe(int pipefd[2])
{
	int	ret;

	ret = pipe(pipefd);
	if (ret < 0)
		fatal_error("xpipe");
	return (ret);
}

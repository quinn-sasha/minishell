/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:23:34 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/02 16:05:06 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief ビルトイン関数のexit
 *
 * @author yurishik
 * @return exitするので到達はしないはず
 */
int	builtin_exit(char **tokens)
{
	int	status;

	status = 0;
	if (tokens[1] != NULL)
		status = 0; // TODO last_status
	// TODO not numeric
	// TODO multiple arguments
	printf("exit\n");
	exit(status);
	return (0);
}

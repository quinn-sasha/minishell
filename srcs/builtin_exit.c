/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:23:34 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/02 15:23:43 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief ビルトイン関数のexit
 *
 * @author yurishik
 * @return exitするので到達はしないはず
 */
int	builtin_exit(void)
{
	printf("exit\n");
	exit(0);
	return (0);
}

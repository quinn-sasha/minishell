/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   just_for_debug.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:10:52 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/02 19:13:27 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief char **配列を表示する
 *
 * @param arr 配列
 */
void	print_str_array(char **arr)
{
	int	i;

	if (!arr)
	{
		printf("(null)\n");
		return ;
	}
	i = 0;
	while (arr[i])
	{
		printf("[%d]: %s\n", i, arr[i]);
		i++;
	}
}

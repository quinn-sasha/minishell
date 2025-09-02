/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:00:50 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/02 17:21:26 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief パイプの記号であるかどうかを判定する
 *
 * @author yurishik
 * @param c 判定したい文字
 * @return パイプの記号であれば1、そうでなければ0
 */
int	is_pipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

/**
 * @brief パイプの記号が何個あるかをカウントする
 *
 * @author yurishik
 * @param input 入力文字列
 * @return パイプの記号の個数
 */
int	count_pipes(const char *input)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (input && input[i])
	{
		if (input[i] == '|')
			count++;
		i++;
	}
	return (count);
}

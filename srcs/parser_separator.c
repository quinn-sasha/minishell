/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_separator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:00:50 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/03 11:50:49 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief separator(現在はスペースとタブのみ)であるかどうかを判定する, IFS未対応
 *
 * @author yurishik
 * @param c 判定したい文字
 * @return separatorに当てはまるなら1、そうでなければ0
 */
int	is_separator(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

/**
 * @brief トークンが何個あるかをカウントする
 *
 * @author yurishik
 * @param input 入力文字列
 * @return トークン数
 */
 int	count_tokens(char *input)
 {
 	int	i;
 	int	count;
 
 	i = 0;
 	count = 0;
 	while (input[i])
 	{
 		while (is_separator(input[i]))
 			i++;
 		if (input[i])
 			count++;
 		while (input[i] && !is_separator(input[i]))
 			i++;
 	}
 	return (count);
 }
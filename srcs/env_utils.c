/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:22:20 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/16 18:50:01 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 入力文字列からイコールで区切られる前の部分=keyの文字数を返す
 *
 * @author yurishik
 * @param str 環境変数の文字列(USER=yurishikのような形式で入る)
 * @return keyの文字数、もし=が文字列中になければ-1
 */
int	get_key_length(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

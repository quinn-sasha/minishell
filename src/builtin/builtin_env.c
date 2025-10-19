/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:22:58 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/19 13:06:18 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 現在の環境変数とその値を標準出力に表示する（envコマンド）
 *
 * @param argv  コマンド引数の配列 (使わない、何が来ても環境変数の一覧を返す)
 * @param envmap  環境変数マップ (t_map) のポインタ
 * @return SUCCESSを返す
 */
int	builtin_env(t_map *envmap)
{
	t_item	*current;

	current = envmap->head.next;
	if (current == NULL)
	{
		printf("empty env list\n");
		return (SUCCESS);
	}
	while (current != NULL)
	{
		if (current->value != NULL)
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (SUCCESS);
}

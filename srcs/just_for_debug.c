/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   just_for_debug.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:10:52 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/16 15:14:58 by yurishik         ###   ########.fr       */
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

/**
 * @brief t_env構造体のリンクリストをすべて表示する
 *
 * @param head リストの先頭ノードへのポインタ
 */
void	print_env(t_env *head)
{
	t_env	*current;

	if (head == NULL)
	{
		printf("empty env list\n");
		return ;
	}
	current = head;
	while (current != NULL)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:15:39 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/02 16:46:53 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief t_env構造体のLinked Listをすべて表示する
 *
 * @author yurishik
 * @param head リストの先頭ノードへのポインタ
 */
void	builtin_env(t_env *head)
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

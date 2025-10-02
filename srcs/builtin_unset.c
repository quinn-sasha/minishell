/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:24:13 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/02 15:24:19 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief unset_envのnorminette対応用
 */
void	unset_mid_node(t_env *prev, t_env *current)
{
	if (current != NULL)
	{
		prev->next = current->next;
		env_delone(current);
	}
}

/**
 * @brief 環境変数を名前で指定してunsetする
 *
 * @author yurishik
 * @param head t_envのLinked Listの先頭
 * @param name unsetしたい環境変数名
 * @return 環境変数名としてOKならFLG_TRUE, NGならFLG_FALSE
 */
int	builtin_unset(t_env **head, const char *name)
{
	t_env	*current;
	t_env	*prev;

	if (head == NULL || name == NULL)
		return (FAILURE);
	if (*head != NULL && ft_strcmp((*head)->key, name) == 0)
	{
		current = *head;
		*head = current->next;
		env_delone(current);
		return (SUCCESS);
	}
	prev = *head;
	if (prev == NULL)
		return (SUCCESS);
	current = prev->next;
	while (current != NULL && ft_strcmp(current->key, name) != 0)
	{
		prev = current;
		current = current->next;
	}
	unset_mid_node(prev, current);
	return (SUCCESS);
}

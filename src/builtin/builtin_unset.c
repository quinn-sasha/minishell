/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:24:13 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/09 16:17:11 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 環境変数を名前で指定してunsetする
 *
 * @author yurishik
 * @param envmap
 * @param name unsetしたい環境変数名
 * @return 環境変数名としてOKならFLG_TRUE, NGならFLG_FALSE
 */
int	builtin_unset(char **argv, t_map *envmap)
{
	t_item	*current;
	t_item	*prev;
	char	*name;

	name = argv[1];
	if (envmap == NULL || name == NULL)
		return (FAILED);
	prev = &(envmap->head);
	current = prev->next;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			prev->next = current->next;
			if (current->name)
				free(current->name);
			if (current->value)
				free(current->value);
			free(current);
			return (SUCCESS);
		}
		prev = current;
		current = current->next;
	}
	return (SUCCESS);
}

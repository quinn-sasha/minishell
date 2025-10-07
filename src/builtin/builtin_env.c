/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:22:58 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/07 14:39:19 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief t_item構造体のLinked Listをすべて表示する
 *
 * @author yurishik
 * @param argv, envmap
 */
int	builtin_env(char **argv, t_map *envmap)
{
	t_item	*current;

    (void)argv;
    current =&(envmap->head);
	if (current == NULL)
	{
		printf("empty env list\n");
        return (0);
	}
	while (current != NULL)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
    return (0);
}

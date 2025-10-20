/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:22:58 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 14:34:46 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (current->value != NULL && current->is_exported)
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (SUCCESS);
}

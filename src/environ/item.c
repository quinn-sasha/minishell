/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:29:53 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 08:29:54 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_item	*new_item(char *name, char *value)
{
	t_item	*item;

	item = xcalloc(1, sizeof(t_item));
	item->name = name;
	item->value = value;
	return (item);
}

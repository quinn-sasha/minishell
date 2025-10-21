/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:29:55 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 08:30:11 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_name_and_value(const char *string, char **name, char **value)
{
	int	name_end;

	name_end = ft_strchr(string, '=');
	if (name_end == NOT_FOUND)
	{
		*name = xstrdup(string);
		*value = NULL;
		return ;
	}
	*name = ft_substr(string, 0, name_end - 1);
	*value = xstrdup(string + name_end + 1);
}

void	map_insert(t_map *map, const char *name, const char *value,
		int is_exported)
{
	t_item	*item;

	if (value == NULL)
		item = new_item(xstrdup(name), NULL);
	else
		item = new_item(xstrdup(name), xstrdup(value));
	item->is_exported = is_exported;
	item->next = map->head.next;
	map->head.next = item;
}

void	map_update_item(t_item *item, const char *value)
{
	free(item->value);
	if (value == NULL)
	{
		item->value = NULL;
		return ;
	}
	item->value = xstrdup(value);
}

void	map_set_internal(t_map *map, char *name, char *value, int is_exported)
{
	t_item	*item;

	item = map_get(map, name);
	if (item)
		map_update_item(item, value);
	else
		map_insert(map, name, value, is_exported);
}

void	map_set(t_map *map, const char *string, int is_exported)
{
	char	*name;
	char	*value;

	set_name_and_value(string, &name, &value);
	if (!is_identifier(name))
	{
		free(name);
		free(value);
		return ;
	}
	map_set_internal(map, name, value, is_exported);
	free(name);
	free(value);
}

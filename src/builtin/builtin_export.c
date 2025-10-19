/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:51:24 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/19 20:55:08 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_item	**extract_items_to_array(t_map *envmap, size_t count)
{
	t_item	**item_array;
	t_item	*current;
	size_t	i;

	if (count == 0)
		return (NULL);
	item_array = (t_item **)xcalloc(count, sizeof(t_item *));
	current = envmap->head.next;
	i = 0;
	while (current != NULL)
	{
		item_array[i] = current;
		current = current->next;
		i++;
	}
	return (item_array);
}

void	bubble_sort_items(t_item **array, size_t count)
{
	size_t	i;
	size_t	j;
	t_item	*temp;

	i = 0;
	while (i < count)
	{
		j = 0;
		while (j < count - 1 - i)
		{
			if (ft_strcmp(array[j]->name, array[j + 1]->name) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

t_item	**map_sort(t_map *envmap)
{
	size_t	count;
	t_item	**item_array;

	if (envmap == NULL)
		return (NULL);
	count = count_map_item(envmap);
	if (count == 0)
		return (NULL);
	item_array = extract_items_to_array(envmap, count);
	if (!item_array)
		return (NULL);
	bubble_sort_items(item_array, count);
	return (item_array);
}

int	display_map_ordered(t_map *envmap)
{
	t_item	**sorted_array;
	size_t	count;
	size_t	i;

	count = count_map_item(envmap);
	if (count == 0)
		return (SUCCESS);
	sorted_array = map_sort(envmap);
	i = 0;
	while (sorted_array && i < count && sorted_array[i])
	{
		if (ft_strcmp(sorted_array[i]->name, "_") != 0)
		{
			if (sorted_array[i]->value != NULL && sorted_array[i]->is_exported)
				ft_dprintf(STDOUT_FILENO, "declare -x %s=\"%s\"\n",
					sorted_array[i]->name, sorted_array[i]->value);
			else if (sorted_array[i]->is_exported)
				ft_dprintf(STDOUT_FILENO, "declare -x %s\n",
					sorted_array[i]->name);
		}
		i++;
	}
	free(sorted_array);
	return (SUCCESS);
}

int	builtin_export(char **argv, t_map *envmap)
{
	int		i;
	char	*name;
	char	*value;
	int		status;

	i = 1;
	status = SUCCESS;
	if (argv[1] == NULL)
		return (display_map_ordered(envmap));
	while (argv[i] != NULL)
	{
		set_name_and_value(argv[i], &name, &value);
		if (!is_identifier(name))
		{
			perror_wrapper("export", name, "not a valid identifier");
			status = 1;
		}
		else
			map_set(envmap, argv[i], TRUE);
		free(name);
		free(value);
		i++;
	}
	return (status);
}

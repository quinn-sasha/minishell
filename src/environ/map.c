#include "minishell.h"

t_item *map_get(t_map* map, const char *name) {
  t_item *iter;
  iter = map->head.next;
  while (iter) {
    if (ft_strcmp(iter->name, name) == 0) {
      return iter;
    }
    iter = iter->next;
  }
  return NULL;
}

/*
* @return: もし削除が最高したらSUCESS、失敗したらFAILEDを返す
*/
int map_delete(t_map *map, const char *name) {
  t_item *prev = &map->head;
  t_item *node = map->head.next;
  while (node) {
    if (ft_strcmp(node->name, name) == 0) {
      prev->next = node->next;
      free(node->name);
      free(node->value);
      free(node);
      return SUCCESS;
    }
    prev = prev->next;
    node = node->next;
  }
  return FAILED;
}

char *xgetenv(t_map *envmap, const char *name) {
  t_item *item = map_get(envmap, name);
  if (item == NULL)
    return NULL;
  return item->value;
}

size_t	count_map_item(t_map *envmap)
{
	t_item	*item;
	size_t	count;

	if (envmap == NULL)
		return (0);
	count = 0;
	item = envmap->head.next;
	while (item != NULL)
	{
		count++;
		item = item->next;
	}
	return (count);
}

char	**get_envmap(t_map *envmap)
{
	char	**env_array;
	t_item	*item;
	size_t	count;
	size_t	i;
	const char	*value;

	if (envmap == NULL)
		return (xcalloc(1, sizeof(char *)));
	count = count_map_item(envmap);
	env_array = (char **)xcalloc(count + 1, sizeof(char *));
	item = envmap->head.next;
	i = 0;
	while (item != NULL)
	{
		if (item->value == NULL)
			value = "";
		else
			value = item->value;
		env_array[i] = join_str_separator(item->name, value, '=');
		item = item->next;
		i++;
	}
	return (env_array);
}

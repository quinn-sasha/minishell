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

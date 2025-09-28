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

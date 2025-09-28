#include "minishell.h"

t_item *new_item(char *name, char *value) {
  t_item *item = xcalloc(1, sizeof(t_item));
  item->name = name;
  item->value = value;
  return item;
}

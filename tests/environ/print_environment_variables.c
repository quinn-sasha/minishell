#include "minishell.h"

int main() {
  t_map *envmap = init_environment();
  t_item *iter = envmap->head.next;
  printf("(name: value)\n");
  while (iter) {
    printf("(%s, %s)\n", iter->name, iter->value);
    iter = iter->next;
  }
  clean_environment(envmap);
  printf("--- END ---\n");
}

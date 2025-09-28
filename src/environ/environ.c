#include "minishell.h"

t_map *init_environment(void) {
  extern char **environ;
  t_map *envmap = xcalloc(1, sizeof(t_map));
  while (*environ) {
    map_set(envmap, *environ);
    environ++;
  }
  char cwd[PATH_MAX];
  if (map_get(envmap, "PWD") == NULL) {
    if (getcwd(cwd, PATH_MAX) == NULL)
      perror_wrapper("init_envmap()", "get_cwd()", NULL);
    else
      map_set_internal(envmap, "PWD", cwd);
  }
  map_set_internal(envmap, "OLDPWD", NULL);
  return envmap;
}


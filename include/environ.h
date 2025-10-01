#ifndef ENVIRON_H
#define ENVIRON_H

typedef struct s_item t_item;
typedef struct s_map t_map;

struct s_item {
  char *name;
  char *value; // value can be NULL
  t_item *next; // Next element or NULL
};

struct s_map {
  t_item head;
  int last_status;
};

// is_identifier.c
bool is_alpha_underscore(int c);
bool is_identifier(const char *s);
// map_set.c
void set_name_and_value(const char *string, char **name, char **value);
void map_insert(t_map *map, const char *name, const char *value);
void map_update_item(t_item *item, const char *value);
void map_set_internal(t_map *map, char *name, char *value);
void map_set(t_map *map, const char *string);
// map.c
t_item *map_get(t_map* map, const char *name);
int map_delete(t_map *map, const char *name);
// item.c
t_item *new_item(char *name, char *value);
// environ.c
t_map *init_environment(void);

#endif

#ifndef ENVIRON_H
#define ENVIRON_H

typedef struct s_item t_item;
typedef struct s_map t_map;

struct s_item {
  char *name;
  char *value;
  t_item *next; // Next element or NULL
};

struct s_map {
  t_item head;
};

#endif

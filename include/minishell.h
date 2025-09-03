#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../libft/libft.h"

#define TRUE 1
#define SUCCESS 0
#define FAILED -1

typedef struct s_word_list {
  struct s_word_list *next;
  char *word;
} t_word_list;

typedef struct s_command {
  t_word_list *words;
} t_command;

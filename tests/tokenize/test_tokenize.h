#include "../../include/minishell.h"

typedef struct s_expected_token {
  t_token_kind token_kind;
  char *word;
} t_expected_token;


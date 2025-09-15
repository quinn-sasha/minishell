#include "../../include/minishell.h"

typedef struct s_expected_token {
  t_token_kind token_kind;
  char *word;
} t_expected_token;

bool assert_tokens_equal(t_token *token, t_expected_token *expected_tokens, int size);
void test_simple_command();

#include "minishell.h"

void free_token(t_token *token) {
  while (!at_eof(token)) {
    t_token *next = token->next;
    free(token->word);
    free(token);
    token = next;
  }
  free(token);
}

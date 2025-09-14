#include "../../include/minishell.h"

bool at_eof(t_token *token) {
  if (token == NULL)
    return false;
  return token->token_kind == TOKEN_EOF;
}

bool is_same_operator(t_token *token, char *operator) {
  if (token->token_kind != TOKEN_OPERATOR)
    return false;
  if (ft_strncmp(token->word, operator, ft_strlen(operator)) == 0)
    return true;
  return false;
}

t_token *new_token(t_token_kind token_kind, char *word) {
  t_token *new_token = xcalloc(1, sizeof(t_token));
  new_token->token_kind = token_kind;
  new_token->word = word;
  new_token->next = NULL;
  return new_token;
}

t_token *duplicate_token(t_token *token) {
  char *word = xstrdup(token->word);
  t_token *result = new_token(token->token_kind, word);
  return result;
}

void append_token

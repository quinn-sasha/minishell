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



#include "minishell.h"

bool at_eof(t_token *token) {
  if (token == NULL)
    return false;
  return token->token_kind == TOKEN_EOF;
}

t_token *new_token(t_token_kind token_kind, char *word) {
  t_token *new_token = xcalloc(1, sizeof(t_token));
  new_token->token_kind = token_kind;
  new_token->word = word;
  new_token->is_expanded = false;
  new_token->next = NULL;
  return new_token;
}

t_token *duplicate_token(t_token *token) {
  char *word = xstrdup(token->word);
  t_token *result = new_token(token->token_kind, word);
  return result;
}

/*
* @param: 追加される対象のトークン.
* @param: 追加するトークン.
* token の末尾に、element が追加される.
* CAUTION: token の末尾が TOKEN_EOF ではなく、NULL で示されているが、
*          最終的に、呼び出し側の make_simple_command() で TOKEN_EOF が挿入される.
*/
void append_token(t_token **head, t_token *element) {
  if (*head == NULL) {
    *head = element;
    return;
  }
  t_token *iter = *head;
  while (iter->next) {
    iter = iter->next;
  }
  iter->next = element;
}

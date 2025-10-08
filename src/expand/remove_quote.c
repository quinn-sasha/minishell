#include "minishell.h"

void remove_quote_word(char **word) {
  if (!is_quote(**word))
    assert_error("remove_quote_word(): a word was not quoted");
  char *to_free = *word;
  int end = ft_strlen(*word);
  char *new_word = ft_substr(*word, 1, end - 2);
  *word = new_word;
  free(to_free);
}

void remove_quote_token(t_token *token) {
  if (token == NULL)
    return;
  t_token *iter = token;
  while (!at_eof(iter)) {
    if (!iter->is_quoted) {
      iter = iter->next;
      continue;
    }
    remove_quote_word(&iter->word);
    iter = iter->next;
  }
}

void remove_quote_redirect(t_redirect *redirect) {
  if (redirect == NULL)
    return;
  t_redirect *iter = redirect;
  while (iter) {
    if (!iter->is_filename_quoted) {
      iter = iter->next;
      continue;
    }
    remove_quote_word(&iter->to.filename);
    iter = iter->next;
  }
}

void remove_quote(t_simple_command *command) {
  remove_quote_token(command->arguments);
  remove_quote_redirect(command->redirect);
}

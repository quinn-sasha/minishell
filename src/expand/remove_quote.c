#include "minishell.h"

void remove_quote_word(char **word_to_modify) {
  char *new_word = xcalloc(1, sizeof(char));
  char *old_word = *word_to_modify;
  int i = 0;
  while (old_word[i]) {
    if (is_quote_marker(old_word[i])) {
      i++;
      continue;
    }
    append_character(&new_word, old_word[i]);
    i++;
  }
  free(old_word);
  *word_to_modify = new_word;
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

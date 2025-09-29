#include "minishell.h"

// $not_exist みたいな存在しない変数は空文字列に展開されるので、trueを返す
bool need_to_expand(char *word) {
  if (*word == SINGLE_QUOTE_CHARCTER)
    return false;
  while (*word) {
    if (*word == '$')
      return true;
    word++;
  }
  return false;
}

void expand_variable() {

}

void expand_word(char **word) {
  if (!need_to_expand(*word)) {
    return;
  }
  char *new_word = xcalloc(1, sizeof(char));
  char *iter = *word;
  while (iter) {
    if (*iter != '$') {
      append_char(&new_word, *iter);
      iter++;
      continue;
    }
    // todo: expand variable
  }
  *word = new_word;
}

void expand_token_words(t_token *token) {
  while (!at_eof(token)) {
    expand_word(&token->word);
    token = token->next;
  }
}

// リダイレクト先のファイル名のみを展開する. here_doc_eofは展開しない.
void expand_redirect_words(t_redirect *redirect) {

}

void expand_shell_parameter(t_simple_command *command, t_map *envmap) {
  t_simple_command *iter = command;
  while (iter) {
    expand_token_words(iter->arguments);
    expand_redirect_words(iter->redirect);
    iter = iter->next;
  }
}

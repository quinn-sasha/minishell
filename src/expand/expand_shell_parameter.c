#include "minishell.h"

// $not_exist みたいな存在しない変数は空文字列に展開されるので、trueを返す
/*
展開する条件は:
- $記号が含まれている
- $記号の次の文字が、アルファベット、アンダースコア（'_'）、もしくは特別な記号('?')
*/
bool need_to_expand(char *word) {
  if (*word == SINGLE_QUOTE_CHARCTER)
    return false;
  int dollar_position = ft_strchr(word, '$');
  if (dollar_position == NOT_FOUND) {
    return false;
  }
  if (is_special_parameter(word + dollar_position)) {
    return true;
  }
  if (is_alpha_underscore(word[dollar_position + 1])) {
    return true;
  }
  return false;
}

void expand_parameter(char **new_word, char **iter_to_return, char *iter, t_map *envmap) {
  iter++;
  if (!is_alpha_underscore(*iter)) {
    assert_error("Invalid variable was not to be exapanded, but now in expand_parameter()");
  }
  char *name = xcalloc(1, sizeof(char));
  while (is_alpha_underscore_num(*iter)) {
    append_character(&name, *iter);
    iter++;
  }
  *iter_to_return = iter;
  char *expanded = xgetenv(envmap, name);
  free(name);
  if (expanded == NULL) {
    return;
  }
  append_string_to_string(new_word, expanded);
}

void expand_word(char **word, t_map *envmap) {
  if (!need_to_expand(*word)) {
    return;
  }
  char *new_word = xcalloc(1, sizeof(char));
  char *iter = *word;
  while (iter) {
    if (*iter != '$') {
      append_character(&new_word, *iter);
      iter++;
      continue;
    }
    if (is_special_parameter(iter)) {
      expand_special_parameter(new_word, &iter, iter, envmap->last_status);
      continue;
    }
    expand_parameter(&new_word, &iter, iter, envmap);
  }
  *word = new_word;
}

void expand_token_words(t_token *token, t_map *envmap) {
  while (!at_eof(token)) {
    expand_word(&token->word, envmap);
    token = token->next;
  }
}

// リダイレクト先のファイル名のみを展開する. here_doc_eofは展開しない.
void expand_redirect_words(t_redirect *redirect, t_map *envmap) {
  while (redirect) {
    if (redirect->redirect_kind == r_reading_until) {
      redirect = redirect->next;
      continue;
    }
    expand_word(&(redirect->to.filename), envmap);
    redirect = redirect->next;
  }
}

void expand_shell_parameter(t_simple_command *command, t_map *envmap) {
  t_simple_command *iter = command;
  while (iter) {
    expand_token_words(iter->arguments, envmap);
    expand_redirect_words(iter->redirect, envmap);
    iter = iter->next;
  }
}

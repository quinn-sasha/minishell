#include "minishell.h"

// $not_exist みたいな存在しない変数は空文字列に展開されるので、trueを返す
/*
展開する条件は:
- $記号が含まれている
- $記号の次の文字が、アルファベット、アンダースコア（'_'）、もしくは特別な記号('?')
*/
bool need_to_expand(char *word) {
  if (ft_strchr(word, '$') == NOT_FOUND)
    return false;
  char *c_ptr = word;
  while (*c_ptr) {
    if (*c_ptr == SINGLE_QUOTE_MARKER) {
      consume_quoted_word(&c_ptr, c_ptr);
      continue;
    }
    if (*c_ptr != '$') {
      c_ptr++;
      continue;
    }
    if (is_special_parameter(c_ptr))
      return true;
    if (is_alpha_underscore(*(c_ptr + 1)))
      return true;
    c_ptr++;
  }
  return false;
}

void expand_parameter(char **new_word, char **char_ptr_to_return, char *char_ptr, t_map *envmap) {
  char_ptr++;
  if (!is_alpha_underscore(*char_ptr)) {
    assert_error("Invalid variable was not to be exapanded, but now in expand_parameter()");
  }
  char *name = xcalloc(1, sizeof(char));
  while (is_alpha_underscore_num(*char_ptr)) {
    append_character(&name, *char_ptr);
    char_ptr++;
  }
  *char_ptr_to_return = char_ptr;
  char *expanded = xgetenv(envmap, name);
  free(name);
  if (expanded == NULL) {
    return;
  }
  append_string_to_string(new_word, expanded);
}

/*
* @return: もし展開されたら EXPANDED、それ以外は NOT_EXPANDED を返す
*/
void expand_word(char **word, t_map *envmap) {
  char *new_word = xcalloc(1, sizeof(char));
  char *char_ptr = *word;
  while (*char_ptr) {
    if (*char_ptr != '$') {
      append_character(&new_word, *char_ptr);
      char_ptr++;
      continue;
    }
    if (is_special_parameter(char_ptr)) {
      expand_special_parameter(&new_word, &char_ptr, char_ptr, envmap->last_status);
      continue;
    }
    expand_parameter(&new_word, &char_ptr, char_ptr, envmap);
  }
  free(*word);
  *word = new_word;
}

void expand_token_words(t_token *token, t_map *envmap) {
  while (!at_eof(token)) {
    if (need_to_expand(token->word)) {
      expand_word(&token->word, envmap);
      token->is_expanded = true;
    }
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
    if (expand_word(&(redirect->to.filename), envmap) == EXPANDED) {
      redirect->is_filename_expanded = true;
    }
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

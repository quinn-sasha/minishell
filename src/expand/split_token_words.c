#include "minishell.h"

static bool is_default_ifs(int c) {
  if (c == ' ')
    return true;
  if (c == '\t')
    return true;
  if (c == '\n')
    return true;
  return false;
}

static int get_word_end(const char *s, int start) {
  int i = start;
  while (!is_default_ifs(s[i])) {
    i++;
  }
  return i;
}

/*
* 不要なトークンが作成されるので、これは後の処理で取り除く必要がある.
* 例えば token->word が空文字列または NULL になっているものは除外する必要がある.
*/
void split_token_word(t_token *token) {
  if (*(token->word) == '\0')
    return;
  char *trimmed = ft_strtrim(token->word, DEFAULT_IFS_CHARS);
  if (*trimmed == '\0') {
    free(trimmed);
    return;
  }
  char *to_free = token->word;
  int start = 0;
  while (trimmed[start]) {
    if (is_default_ifs(trimmed[start])) {
      start++;
      continue;
    }
    int end = get_word_end(trimmed, start);
    token->word = ft_substr(trimmed, start, end - 1);
    insert_next_token(token, new_token(TOKEN_WORD, NULL));
    token = token->next;
    start = end;
  }
  free(trimmed);
  free(to_free);
}

void split_token_words(t_token *token) {
  while (!at_eof(token)) {
    if (token->is_expanded) {
      split_token_word(token);
    }
    token = token->next;
  }
}

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
  if (is_default_ifs(s[start]))
    assert_error("get_word_end(): first character of word is IFS character");
  int i = start;
  while (s[i]) {
    if (is_default_ifs(s[i]))
      return i;
    if (!is_quote_marker(s[i])) {
      i++;
      continue;
    }
    char quote = s[i];
    i++;
    while (s[i] != quote)
      i++;
    i++;
  }
  return i;
}

/*
* 不要なトークンがリストの末尾（実際の末尾は TOKE_EOF）に作成されるので、これは後の処理で取り除く必要がある.
* その末尾トークンの token->word は NULL になっている.
*/
void split_token_word(t_token *token) {
  char *trimmed = ft_strtrim(token->word, DEFAULT_IFS_CHARS);
  if (*trimmed == '\0') {
    free(trimmed);
    free(token->word);
    token->word = NULL;
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
    token->next->is_quoted = token->is_quoted;
    token = token->next;
    start = end;
  }
  free(trimmed);
  free(to_free);
}

// 分割して増えたトークンは、is_expanded == false になっている
void split_token_words(t_token *token) {
  t_token *iter = token;
  while (!at_eof(iter)) {
    if (!iter->is_expanded) {
      iter = iter->next;
      continue;
    }
    split_token_word(iter);
    iter = iter->next;
  }
}

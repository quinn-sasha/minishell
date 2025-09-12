#include "../include/minishell.h"

t_word_list *new_word_list(char *word) {
  t_word_list *result = malloc(sizeof(t_word_list));
  result->word = word;
  result->next = NULL;
  return result;
}

/*
inputを解析して、解析した結果を返す。
コマンド名とオプションをword_list構造体にいれる。
クオートには対応していない。
*/
int parse(char *input, t_command *command) {
  t_word_list *dummy_head = new_word_list(NULL);
  t_word_list *words = dummy_head;
  int i = 0;
  while (input[i]) {
    if (is_blank(input[i])) {
      i++;
      continue;
    }
    int word_start = i;
    while (input[i] && !is_blank(input[i])) {
      i++;
    }
    char *word = ft_substr(input, word_start, i - 1);
    words->next = new_word_list(word);
    words = words->next;
  }
  command->words = dummy_head->next;
  free(dummy_head);
  return SUCCESS;
}

/*
リンクトリストから文字列の配列に変換する。
wordsには最低でも一つの文字列が入っていると仮定する。
*/
char **convert_word_list_to_string_array(t_word_list *words) {
  int num_words = 0;
  t_word_list *iter = words;
  while (iter) {
    num_words++;
    iter = iter->next;
  }
  char **result = ft_calloc(num_words + 1, sizeof(char *));
  int i = 0;
  iter = words;
  while (i < num_words) {
    result[i] = iter->word;
    i++;
    iter = iter->next;
  }
  return result;
}

bool is_same_operator(t_token *token, char *operator) {
  if (token->token_kind != TOKEN_OPERATOR)
    return false;
  if (ft_strncmp(token->word, operator, ft_strlen(operator)) == 0)
    return true;
  return false;
}

/*
Syntax error:
- パイプ `|` の左にコマンドがない
- パイプ `|` の右にコマンドがない
- パイプ `|` の次に control operator ( | ) がくる
- リダイレクト (`>` `<` `<<` `>>` ) の次に word が来ない
- クオートが閉じられていない (tokenize()で対応済み)
*/
bool is_valid_syntax(t_token *token) {
  if (is_same_operator(token, PIPE)) {
    // throw error
    return false;
  }
  while (!at_eof(token)) {
    if (token->token_kind == TOKEN_WORD) {
      token = token->next;
      continue;
    }
    if (is_same_operator(token, PIPE) &&
        is_same_operator(token->next, PIPE)) {
      // throw error
      return false;
    }
    if (!is_same_operator(token, PIPE) &&
        token->next->token_kind == TOKEN_OPERATOR) {
      // throw error
      return false;
    }
    token = token->next;
  }
  return true;
}

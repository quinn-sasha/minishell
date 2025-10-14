#include "minishell.h"

/*
blank
  A space or tab character.

control operator
  A token that performs a control function. It is a newline or '|'.

metacharacter
  A character that, when unquoted, separates words. A metacharacter is
  a space, tab, newline, or one of the following characters: ‘|’, ‘<’, or ‘>’.

token
  A sequence of characters considered a single unit by the shell.
  It is either a word or an operator.

operator
  A control operator or a redirection operator. See Redirections, for a list of
  redirection operators. Operators contain at least one unquoted metacharacter.

word
  A sequence of characters treated as a unit by the shell.
  Words may not include unquoted metacharacters.
*/

int is_blank(int c) {
  if (c == ' ' || c == '\t')
    return true;
  return false;
}

bool is_quote(int c) {
  if (c == SINGLE_QUOTE_MARKER)
    return true;
  if (c == DOUBLE_QUOTE_MARKER)
    return true;
  if (c == SINGLE_QUOTE_CHARCTER)
    return true;
  if (c == DOUBLE_QUOTE_CHARACTER)
    return true;
  return false;
}

int is_metacharacter(int c) {
  if (is_blank(c))
    return true;
  return ft_strchr("|<>", c) != NOT_FOUND;
}

/*
* @param オペレータの文字数ぶん前に進めるinput. 呼び出し元にも反映される.
* @param 元のinput文字列.
* @return operator token
*/
t_token *consume_operator(char **input_to_return, char *input) {
  static const char *operators[] = {"<<", ">>", "<", ">", "|", NULL};
  int i = 0;
  while (operators[i]) {
    if (ft_strncmp(input, operators[i], ft_strlen(operators[i])) != 0) {
      i++;
      continue;
    }
    char *word = ft_strdup(operators[i]);
    t_token *result = new_token(TOKEN_OPERATOR, word);
    *input_to_return += ft_strlen(operators[i]);
    return result;
  }
  return NULL;
}

/*
* @brief: クオートマーカー記号が来たら、対応する文字の次の文字まで input_to_return を進める.
*/
void consume_quoted_word(char **input_to_return, char *input) {
  int i = 0;
  char quote = input[i];
  i++;
  while (input[i] && input[i] != quote)
    i++;
  if (input[i] == '\0')
    assert_error("Word is not quoted");
  i++;
  *input_to_return += i;
}

/*
* @param wordの文字数ぶん前に進めるinput. 呼び出し元にも反映される.
* @param 元のinput文字列.
* @return word token
*/
t_token *consume_word(char **input_to_return, char *input) {
  bool is_quoted_flag = false;
  int word_end = 0;
  while (input[word_end]) {
    if (is_metacharacter(input[word_end]))
      break;
    if (!is_quote(input[word_end])) {
      word_end++;
      continue;
    }
    consume_quoted_word(&input, input);
    is_quoted_flag = true;
  }
  char *word = ft_substr(input, 0, word_end - 1);
  t_token *result = new_token(TOKEN_WORD, word);
  result->is_quoted = is_quoted_flag;
  *input_to_return += word_end;
  return result;
}

/*
* @param wordの文字数ぶん前に進めるinput. 呼び出し元にも反映される.
* @param 元のinput文字列.
* @param もしシングルクオートエラーであれば、エラーステータスが設定される.
* @return word token
*/
t_token *consume_quoted_word(char **input_to_return, char *input, int *status) {
  char quote_to_match = SINGLE_QUOTE_CHARCTER;
  if (*input == DOUBLE_QUOTE_CHARACTER) {
    quote_to_match = DOUBLE_QUOTE_CHARACTER;
  }
  int word_end = 1;
  while (input[word_end]) {
    if (input[word_end] == quote_to_match) {
      break;
    }
    word_end++;
  }
  if (input[word_end] == '\0') {
    unclosed_quote_error();
    *status = UNCLOSED_QUOTE_STATUS;
    word_end--;
  }
  char *word = ft_substr(input, 0, word_end);
  t_token *result = new_token(TOKEN_WORD, word);
  result->is_quoted = true;
  *input_to_return += word_end + 1;
  return result;
}

bool is_quote_closed(char *input) {
  while (*input) {
    if (!is_quote(*input)) {
      input++;
      continue;
    }
    char quote_to_match = *input;
    while (*input && *input != quote_to_match) {
      input++;
    }
    if (*input == '\0')
      return false;
    input++;
  }
  return true;
}

char get_quote_marker(int quote) {
  if (quote == SINGLE_QUOTE_CHARCTER)
    return SINGLE_QUOTE_MARKER;
  return DOUBLE_QUOTE_MARKER;
}

void replace_quote_char_with_marker(char **input_to_modify, char *input) {
  int i = 0;
  while (input[i]) {
    if (!is_quote(input[i])) {
      i++;
      continue;
    }
    char quote = input[i];
    (*input_to_modify)[i] = get_quote_marker(quote);
    i++;
    while (input[i] != quote)
      i++;
    (*input_to_modify)[i] = get_quote_marker(quote);
    i++;
  }
}

/*
* @param command line input.
* @return inputをトークン化したリスト. リストの最後の要素はTOKEN_EOFタイプ.
          もしエラーが起これば NULL を返す.
*/
t_token *tokenize(char *input) {
  t_token dummy;
  dummy.next = NULL;
  t_token *token = &dummy;

  if (!is_quote_closed(input)) {
    unclosed_quote_error();
    return NULL;
  }
  replace_quote_char_with_marker(&input, input);
  while (*input) {
    if (is_blank(*input)) {
      input++;
      continue;
    }
    if (is_metacharacter(*input)) {
      token->next = consume_operator(&input, input);
      token = token->next;
      continue;
    }
    token->next = consume_word(&input, input);
    token = token->next;
  }
  token->next = new_token(TOKEN_EOF, NULL);
  return dummy.next;
}

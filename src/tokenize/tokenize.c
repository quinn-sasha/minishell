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
    return TRUE;
  return FALSE;
}

int is_quote(int c) {
  if (c == SINGLE_QUOTE_CHARCTER || c == DOUBLE_QUOTE_CHARACTER)
    return TRUE;
  return FALSE;
}

int is_metacharacter(int c) {
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
* @param wordの文字数ぶん前に進めるinput. 呼び出し元にも反映される.
* @param 元のinput文字列.
* @return word token
*/
t_token *consume_word(char **input_to_return, char *input) {
  int i = 0;
  while (input[i]) {
    if (is_blank(input[i]))
      break;
    i++;
  }
  char *word = ft_substr(input, 0, i - 1);
  t_token *result = new_token(TOKEN_WORD, word);
  *input_to_return += i;
  return result;
}

/*
* @param wordの文字数ぶん前に進めるinput. 呼び出し元にも反映される.
* @param 元のinput文字列.
* @param もしシングルクオートエラーであれば、エラーステータスが設定される.
* @return word token
*/
t_token *consume_quoted_word(char **input_to_return, char *input, int *error_status) {
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
    *error_status = UNCLOSED_QUOTE_STATUS;
    word_end--;
  }
  char *word = ft_substr(input, 0, word_end);
  t_token *result = new_token(TOKEN_WORD, word);
  *input_to_return += word_end + 1;
  return result;
}

/*
* @param command line input.
* @param トークン化の結果を保持する.TOKENIZE_SUCCESS or SINGLE_QUOTE_ERROR.
*        もしエラーであれば呼び出し側は返り値を解放する.
* @return inputをトークン化したリスト. リストの最後の要素はTOKEN_EOFタイプ.
*/
t_token *tokenize(char *input, int *error_status) {
  t_token dummy;
  dummy.next = NULL;
  t_token *token = &dummy;

  *error_status = TOKENIZE_SUCCESS;
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
    if (is_quote(*input)) {
      token->next = consume_quoted_word(&input, input, error_status);
      token = token->next;
      continue;
    }
    token->next = consume_word(&input, input);
    token = token->next;
  }
  token->next = new_token(TOKEN_EOF, NULL);
  return dummy.next;
}

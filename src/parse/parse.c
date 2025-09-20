#include "minishell.h"

/*
How to interpret input.

<pipeline> = <simple_command> ('|' <pipeline>)
<simple_command> = <command_element>+
<command_element> = <word> | <redirection>
<redirection> = '>' <word>
              | '<' <word>
              | '>>' <word>
              | '<<' <word>
*/
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
  if (is_same_operator(token, PIPE_SYMBOL)) {
    syntax_error(token->word);
    return false;
  }
  while (!at_eof(token)) {
    if (token->token_kind == TOKEN_WORD) {
      token = token->next;
      continue;
    }
    if (token->next->token_kind == TOKEN_EOF) {
      syntax_error("newline");
      return false;
    }
    if (is_same_operator(token, PIPE_SYMBOL) &&
        is_same_operator(token->next, PIPE_SYMBOL)) {
      syntax_error(token->word);
      return false;
    }
    if (!is_same_operator(token, PIPE_SYMBOL) &&
        token->next->token_kind == TOKEN_OPERATOR) {
      syntax_error(token->next->word);
      return false;
    }
    token = token->next;
  }
  return true;
}

/*
* @param: 実行部に渡すコマンド構造体. parse()を呼び出した時点では動的に割り当てられていない.
* @param: トークンのリスト.
* @return: PARSE_SUCCESS or PARSE_SYNTAX_ERROR
* トークンからコマンド構造体をつくる.
* parse()が成功した場合、以下の状態が達成されている.
*   simple command 構造体が初期化されている.
*   tokenize()の返り値であるトークンが解放されている.
*/
int parse(t_simple_command **command, t_token *token) {
  if (!is_valid_syntax(token)) {
    free_token(token);
    return PARSE_SYNTAX_ERROR;
  }
  *command = make_simple_command_list(token);
  free_token(token);
  return PARSE_SUCCESS;
}

#include "../include/minishell.h"

/*
* @param: 実行部に渡すコマンド構造体. 動的に割り当てる.
* @param: トークンのリスト.
* @return: PARSE_SUCCESS, PARSE_SYNTAX_ERROR or PARSE_MALLOC_FAILED
* トークンからコマンド構造体をつくる.
* parse()が成功した場合、以下の状態が達成されている.
*   simple command 構造体が初期化されている.
*   子プロセスがコマンドの数ぶん作られる.
*   パイプがあれば、コマンドの読み込み口か書き込み口に向けられている.
*/
int parse(t_simple_command **command, t_token *token) {

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
    if (is_same_operator(token, PIPE) &&
        is_same_operator(token->next, PIPE)) {
      syntax_error(token->word);
      return false;
    }
    if (!is_same_operator(token, PIPE) &&
        token->next->token_kind == TOKEN_OPERATOR) {
      syntax_error(token->next->word);
      return false;
    }
    token = token->next;
  }
  return true;
}

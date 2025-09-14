#include "../include/minishell.h"

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
* @param: token to advance until it reaches EOF or pipe. The change will be reflected at caller.
* @param: token
* @return: One simple command
* It creates one simple command.
* It advances token until EOF or next pipe. This advanced token is set to token_to_return.
*/
t_simple_command *make_simple_command(t_token **token_to_return, t_token *token) {
  t_simple_command *command = xcalloc(1, sizeof(t_simple_command));
  while (!at_eof(token) && is_same_operator(token, PIPE_SYMBOL));
  return command;
}

/*
* @param: valid token
* @return: simple command list. operators are removed.
* Make simple command from valid token.
* However, child pid is not assigned in this function,
* but later in prepare_pipeline().
*/
t_simple_command *make_simple_command_list(t_token *token) {
  if (token->token_kind == TOKEN_EOF)
    return NULL;
  t_simple_command *command = make_simple_command(&token, token);
  if (is_same_operator(token, PIPE_SYMBOL)) {
    command->next = make_simple_command_list(token->next);
  }
  return command;
}

/*
* @param: 実行部に渡すコマンド構造体. 動的に割り当てる.
* @param: トークンのリスト.
* @return: PARSE_SUCCESS or PARSE_SYNTAX_ERROR
* トークンからコマンド構造体をつくる.
* parse()が成功した場合、以下の状態が達成されている.
*   simple command 構造体が初期化されている.
*   子プロセスがコマンドの数ぶん作られる.
*   パイプがあれば、コマンドの読み込み口か書き込み口に向けられている.
*/
int parse(t_simple_command **command, t_token *token) {
  if (!is_valid_syntax(token)) {
    free_token(token);
    return PARSE_SYNTAX_ERROR;
  }
  t_simple_command *command = make_simple_command_list(token);
  prepare_pipeline(command);
  return PARSE_SUCCESS;
}

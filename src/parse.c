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
redirectの種類から、redirect構造体のメンバに値を書き込む.
*/
void fill_redirect(t_redirect *redirect, t_redirect_kind r_kind ,t_token *token) {
  redirect->redirect_kind = r_kind;
  if (r_kind == r_input_direction) {
    redirect->from.fd = STDIN_FILENO;
    redirect->to.filename = token->next->word;
    redirect->open_flags = O_RDONLY;
    return;
  }
  if (r_kind == r_output_direction) {
    redirect->from.fd = STDOUT_FILENO;
    redirect->to.filename = token->next->word;
    redirect->open_flags = O_CREAT | O_TRUNC | O_WRONLY;
    return;
  }
  if (r_kind == r_appending_to) {
    redirect->from.fd = STDOUT_FILENO;
    redirect->to.filename = token->next->word;
    redirect->open_flags = O_CREAT | O_APPEND | O_WRONLY;
    return;
  }
  redirect->here_doc_eof = token->next->word;
}

/*
トークンの種類からリダイレクト構造体を作る.
*/
t_redirect *new_redirect(t_token *token) {
  t_redirect *result = xcalloc(1, sizeof(t_redirect));
  if (is_same_operator(token, "<")) {
    fill_redirect(result, r_input_direction, token);
    return result;
  }
  if (is_same_operator(token, ">")) {
    fill_redirect(result, r_output_direction, token);
    return result;
  }
  if (is_same_operator(token, ">>")) {
    fill_redirect(result, r_appending_to, token);
    return result;
  }
  fill_redirect(result, r_reading_until, token);
  return result;
}

/*
コマンド構造体に、command element (定義は以下を参照) が追加される.
進められたトークンが token_to_return に保存される.
<command_element> = <word> | <redirection>
*/
void append_command_element(t_simple_command *command, t_token **token_to_return, t_token *token) {
  if (token->token_kind == TOKEN_WORD) {
    append_token(&command->arguments, token);
    token_to_return = token->next;
    return;
  }
  // t_redirect *redirect = new_redirect(token)
  // append_redirect(&command->redirect, redirect)
  // token_to_return = token->next->next;
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
  while (!at_eof(token) && !is_same_operator(token, PIPE_SYMBOL)) {
    // append command element
  }
  // append token eof
  *token_to_return = token;
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

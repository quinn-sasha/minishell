#include "minishell.h"

/*
コマンド構造体に、command element (定義は以下を参照) が追加される.
進められたトークンが token_to_return に保存される.
<command_element> = <word> | <redirection>
<redirection> = '>' <word>
              | '<' <word>
              | '>>' <word>
              | '<<' <word>
*/
void append_command_element(t_simple_command *command, t_token **token_to_return, t_token *token) {
  if (token->token_kind == TOKEN_WORD) {
    append_token(&command->arguments, token);
    token_to_return = token->next;
    return;
  }
  t_redirect *redirect = new_redirect(token);
  append_redirect(&command->redirect, redirect);
  token = token->next->next;
}

/*
* @param: token to advance until it reaches EOF or pipe. The change will be reflected at caller.
* @param: token
* @return: One simple command
* It creates one simple command.
* In addition, it advances token until EOF or next pipe. This advanced token is set to token_to_return.
*/
t_simple_command *make_simple_command(t_token **token_to_return, t_token *token) {
  t_simple_command *command = xcalloc(1, sizeof(t_simple_command));
  while (!at_eof(token) && !is_same_operator(token, PIPE_SYMBOL)) {
    append_command_element(command, &token, token);
  }
  t_token *tail = new_token(TOKEN_EOF, NULL);
  append_token(command->arguments, tail);
  *token_to_return = token;
  return command;
}

/*
* @param: valid token
* @return: simple command list. operators are removed.
* Make simple command from valid token.
* However, child pid is not assigned in this function,
* but later in prepare_pipeline().
* token eof かのチェックは実は不要だが、関数の独立性が高まるので追加した.
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

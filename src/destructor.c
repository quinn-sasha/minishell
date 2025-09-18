#include "minishell.h"

void free_token(t_token *token) {
  while (!at_eof(token)) {
    t_token *next = token->next;
    free(token->word);
    free(token);
    token = next;
  }
  free(token);
}

/*
* @brief redirect構造体リストを解放する. 解放後にNULLは代入しない.
*        理由は、redirectにアクセスするための command 構造体が解放後に NULL 代入されるから.
*/
void clean_redirect(t_redirect *redirect) {
  if (redirect == NULL)
    return;
  t_redirect *next = redirect->next;
  if (redirect->redirect_kind == r_reading_until) {
    free(redirect->here_doc_eof);
    free(redirect);
    clean_redirect(next);
    return;
  }
  free(redirect->to.filename);
  free(redirect);
  clean_redirect(next);
}

/*
* @brief 動的に割り当てたコマンド構造体のリストを解放する. 解放後は NULL を代入する.
*/
void clean_command(t_simple_command **command) {
  if (*command == NULL) {
    return;
  }
  t_simple_command *next = (*command)->next;
  if ((*command)->arguments) {
    free_token((*command)->arguments);
  }
  if ((*command)->redirect) {
    clean_redirect((*command)->redirect);
  }
  free(command);
  *command = NULL;
  clean_command(&next);
}

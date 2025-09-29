#include "minishell.h"

void expand_token_words(t_token *token) {

}

// リダイレクト先のファイル名のみを展開する. here_doc_eofは展開しない.
void expand_redirect_words(t_redirect *redirect) {

}

void expand_shell_parameter(t_simple_command *command, t_map *envmap) {
  t_simple_command *iter = command;
  while (iter) {
    // expland token
    expand_token_words(command->arguments);

    iter = iter->next;
  }
}

int expand(t_simple_command *command, t_map *envmap) {
  // expand_shell_parameter()
  // check syntax error
  // split_word()
  // remove_quote()
}

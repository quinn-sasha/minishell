#include "../include/minishell.h"

/*
現在はコマンドが一つしかないが、任意の数のコマンドを動的に割り当てる
必要が出てきたら、command自体も解放する。
*/
void clean_command(t_command *command) {
  t_word_list *iter = command->words;
  while (iter) {
    t_word_list *next = iter->next;
    free(iter->word);
    iter = next;
  }
  command = NULL;
}

void free_token(t_token *token) {
  while (!at_eof(token)) {
    t_token *next = token->next;
    free(token->word);
    free(token);
    token = next;
  }
  free(token);
}

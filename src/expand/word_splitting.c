#include "minishell.h"

/*
* @brief is_valid_syntax_after_expansion()で展開されたファイル名が、
* 有効である（単語が一つしかない）ことが保証されているので、
* ファイル名の前後から空白などを取り除く処理だけ行う.
*/
void trim_redirect_filename(t_redirect *redirect) {

}

// split_token_words()によって生じた不要な末尾トークンを削除する
static void remove_unnecessary_tail_token(t_token **token) {
  while (!at_eof(*token) && (*token)->word == NULL) {
    t_token *temp = *token;
    *token = (*token)->next;
    free_token(temp);
  }
  if (at_eof(*token))
    return;
  t_token *iter = *token;
  while (!at_eof(iter)) {
    if (iter->next->word != NULL) {
      iter = iter->next;
      continue;
    }
    t_token *to_remove = iter->next;
    iter->next = iter->next->next;
    free_token(to_remove);
  }
}

/*
* @brief 展開された変数が空になったり、2つ以上になった場合に、トークンを分割する処理を行う
*/
void split_words(t_simple_command *command) {
  // split token words
  remove_unnecessary_tail_token(&command->arguments);
  // split redirect words
}

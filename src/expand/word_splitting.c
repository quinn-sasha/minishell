#include "minishell.h"


/*
* @brief is_valid_syntax_after_expansion()で展開されたファイル名が、
* 有効である（単語が一つしかない）ことが保証されているので、
* ファイル名の前後から空白などを取り除く処理だけ行う.
*/
void trim_redirect_filename(t_redirect *redirect) {

}

/*
* @brief 展開された変数が空になったり、2つ以上になった場合に、トークンを分割する処理を行う
*/
void split_words(t_simple_command *command) {
  // split token words
  // split redirect words
}

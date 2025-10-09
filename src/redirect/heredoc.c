#include "minishell.h"

extern volatile sig_atomic_t g_signal_number;

int stop_readline_if_sigint(void) {
  if (g_signal_number != SIGINT)
    return 0;
  rl_done = true;
  return 0;
}

int read_heredoc_loop(int *pipefd, const char *delimiter) {
  
}

/*
* @brief delimiterが打ち込まれるまで、複数行を読んでコマンドに渡す
* @return 読みこんだ入力が入っているパイプの読み込み口（fd）を返す.
*         読み込み途中で SIGINT を補足したら、-1を返す.
*/
int read_heredoc(const char *delimiter) {
  rl_event_hook = stop_readline_if_sigint;
  int pipefd;
  xpipe(pipefd);

  g_signal_number = 0;
  rl_event_hook = check_state;
}

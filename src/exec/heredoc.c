#include "minishell.h"

extern volatile sig_atomic_t g_signal_number;

int stop_readline_if_sigint(void) {
  if (g_signal_number != SIGINT)
    return 0;
  rl_done = true;
  return 0;
}

char *expand_heredoc_line(char *line, t_map *envmap) {
  char *new_word = xcalloc(1, sizeof(char));
  char *char_ptr = line;
  while (*char_ptr) {
    if (*char_ptr != '$') {
      append_character(&new_word, *char_ptr);
      char_ptr++;
      continue;
    }
    if (is_special_parameter(char_ptr)) {
      expand_special_parameter(&new_word, &char_ptr, char_ptr, envmap->last_status);
      continue;
    }
    expand_parameter(&new_word, &char_ptr, char_ptr, envmap);
  }
  free(line);
  return new_word;
}

/*
* @return: もし読み込み途中に SIGINT シグナルを受けっとたら、HEREDOC_INTERRUPTED を返す.
*          それ以外は HEREDOC_FINISHED を返す.
*/
int read_until_delimiter(int *pipefd, const char *delimiter, bool is_quoted, t_map *envmap) {
  while (true) {
    char *line = readline("(heredoc)> ");
    if (g_signal_number == SIGINT) {
      free(line);
      return HEREDOC_INTERRUPTED;
    }
    if (line == NULL || ft_strcmp(line, delimiter) == 0) {
      free(line);
      return HEREDOC_FINISHED;
    }
    if (!is_quoted)
      line = expand_heredoc_line(line, envmap);
    ft_dprintf(pipefd[WRITE], "%s\n", line);
    free(line);
  }
  return HEREDOC_FINISHED;
}

/*
* @brief delimiterが打ち込まれるまで、複数行を読んでコマンドに渡す
* @return 読みこんだ入力が入っているパイプの読み込み口（fd）を返す.
*         読み込み途中で SIGINT を補足したら、-1を返す.
*/
int read_heredoc(const char *delimiter, bool is_quoted, t_map *envmap) {
  rl_event_hook = stop_readline_if_sigint;
  int pipefd[2];
  xpipe(pipefd);
  int result = read_until_delimiter(pipefd, delimiter, is_quoted, envmap);
  close(pipefd[WRITE]);
  set_up_signal();
  if (result == HEREDOC_INTERRUPTED) {
    close(pipefd[READ]);
    return -1;
  }
  return pipefd[READ];
}

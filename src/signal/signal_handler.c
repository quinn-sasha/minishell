#include "minishell.h"

extern volatile sig_atomic_t g_signal_number;

void signal_handler(int signum) {
  g_signal_number = signum;
}

/*
* @brief: Ctrl-cもしくはCrtl-\が押された時のシグナルハンドラを設定する
*/
void set_signal_handler(int signum) {
  struct sigaction sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0; // Ctrl-c ではシステムコールを中断させたいから SA_RESTART はセットしない
  sa.sa_handler = signal_handler;
  if (sigaction(signum, &sa, NULL) == FAILED) {
    fatal_error("sigaction()");
  }
}

void ignore_signal(int signum) {
  struct sigaction sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sa.sa_handler = SIG_IGN;
  if (sigaction(signum, &sa, NULL) == FAILED) {
    fatal_error("sigaction()");
  }
}

void reset_signal(int signum) {
  struct sigaction sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sa.sa_handler = SIG_DFL;
  if (sigaction(signum, &sa, NULL) == FAILED) {
    fatal_error("sigaction()");
  }
}

int check_state(void) {
  if (g_signal_number == 0) {
    return SUCCESS;
  }
  if (g_signal_number == SIGINT) {
    g_signal_number = 0;
    rl_done = true;
    write(STDERR_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
  }
  return SUCCESS;
}

void set_up_signal(void) {
  g_signal_number = 0;
  set_signal_handler(SIGINT);
  ignore_signal(SIGQUIT);
  rl_outstream = stderr;
  if (isatty(STDIN_FILENO)) {
    rl_event_hook = check_state;
  }
}

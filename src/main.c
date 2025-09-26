#include "minishell.h"

volatile sig_atomic_t g_signal_number;

void interpret(char *input) {
  int status;
  t_token *token = tokenize(input, &status);
  if (status == UNCLOSED_QUOTE_STATUS) {
    free_token(token);
    return;
  }
  if (at_eof(token)) {
    free_token(token);
    return;
  }
  t_simple_command *command = NULL;
  if (parse(&command, token) == PARSE_SYNTAX_ERROR) {
    return;
  }
  // expansion
  // execute
  // clean command
}

int main(void) {
  // initialize environment
  set_up_signal();
  while (TRUE) {
    char *input = readline("micro-shell> ");
    if (input == NULL)
      return;
    if (*input)
      add_history(input);
    interpret(input);
    free(input);
  }
}

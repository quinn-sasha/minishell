#include "minishell.h"

volatile sig_atomic_t g_signal_number;

void interpret(char *input, t_map *envmap) {
  int tokenize_status;
  t_token *token = tokenize(input, &tokenize_status);
  if (tokenize_status == UNCLOSED_QUOTE_STATUS) {
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
  t_map *environment = init_environment()
  set_up_signal();
  while (TRUE) {
    char *input = readline("micro-shell> ");
    if (input == NULL)
      return EXIT_SUCCESS;
    if (*input)
      add_history(input);
    interpret(input, environment);
    free(input);
  }
}

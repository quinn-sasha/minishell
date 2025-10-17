#include "minishell.h"

volatile sig_atomic_t g_signal_number;

void interpret(char *input, t_map *envmap) {
  t_token *token = tokenize(input);
  if (token == NULL)
    return;
  if (at_eof(token)) {
    free_token_list(token);
    return;
  }
  t_simple_command *command = NULL;
  if (parse(&command, token) == PARSE_SYNTAX_ERROR) {
    return;
  }
  if (expand(command, envmap) == EXPAND_SYNTAX_ERROR) {
    clean_command(&command);
    return;
  }
  envmap->last_status =  exec(command, envmap);
  clean_command(&command);
}

int main(void) {
  t_map *environment = init_environment();
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
  clean_environment(environment);
}

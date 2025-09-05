#include "../include/minishell.h"

int main(void) {
  while (TRUE) {
    char *input = readline("> ");
    if (input == NULL)
      exit(EXIT_SUCCESS);
    t_command command;
    parse(input, &command);
    execute_command(command);
    clean_command(&command);
    free(input);
  }
}

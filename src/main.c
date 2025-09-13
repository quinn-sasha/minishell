#include "../include/minishell.h"

int main(void) {
  while (TRUE) {
    char *input = readline("> ");
    if (input == NULL)
      exit(EXIT_SUCCESS);
  }
}

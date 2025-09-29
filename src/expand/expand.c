#include "minishell.h"

void append_character(char **string, int c) {
  char *new_string;
  if (*string == NULL) {
    new_string = xcalloc(2, sizeof(char));
    new_string[0] = c;
    *string = new_string;
    return;
  }
  size_t new_length = ft_strlen(*string) + 1;
  new_string = xcalloc(new_length + 1, sizeof(char));
  ft_strlcpy(new_string, *string, new_length + 1);
  new_string[new_length - 1] = c;
  *string = new_string;
}

int expand(t_simple_command *command, t_map *envmap) {
  // expand_shell_parameter()
  // check syntax error
  // split_word()
  // remove_quote()
}

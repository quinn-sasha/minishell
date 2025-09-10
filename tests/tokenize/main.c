#include "../../include/minishell.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Too few arugments\n");
    return FAILED;
  }
  char *input = argv[1];
  int error_status;
  t_token *tokens = tokenize(input, &error_status);

  if (!input || !*input) {
    printf("Input string is empty\n");
    return SUCCESS;
  }
  if (error_status == UNCLOSED_QUOTE_STATUS) {
    // free tokens;
    ft_putendl_fd(UNCLOSED_QUOTE_ERROR, STDERR_FILENO);
    return FAILED;
  }
  t_token *iter = tokens;
  while (!at_eof(iter)) {
    printf("word: %s\n", iter->word);
    iter = iter->next;
  }
}

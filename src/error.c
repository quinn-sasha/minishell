#include "../include/minishell.h"

void prefix_error(void) {
  ft_putendl_fd(PREFIX_ERROR, STDERR_FILENO);
}

void syntax_error(const char *unexpected_token) {
  prefix_error();
  ft_dprintf(STDERR_FILENO, "syntax error near unexpected token: %s\n", unexpected_token);
}


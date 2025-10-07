#include "minishell.h"

void prefix_error(void) {
  ft_putstr_fd(PREFIX_ERROR, STDERR_FILENO);
}

void unclosed_quote_error(void) {
  prefix_error();
  ft_dprintf(STDERR_FILENO, "syntax error: unclosed quote\n");
}

void syntax_error(const char *unexpected_token) {
  prefix_error();
  ft_dprintf(STDERR_FILENO, "syntax error near unexpected token: %s\n", unexpected_token);
}

void ambiguous_redirect_error(void) {
  prefix_error();
  ft_dprintf(STDERR_FILENO, "ambiguous redirect\n");
}

/*
Call this function when important system calls fail.
It exits the program without freeing resources.
*/
void fatal_error(const char *message) {
  prefix_error();
  ft_dprintf(STDOUT_FILENO, "Fatal error: %s\n", message);
  perror(NULL);
  exit(EXIT_FAILURE);
}

void perror_wrapper(const char *s1, const char *s2, const char *message) {
  prefix_error();
  ft_dprintf(STDERR_FILENO, "%s: ", s1);
  ft_dprintf(STDERR_FILENO, "%s: ", s2);
  if (message)
    ft_dprintf(STDERR_FILENO, "%s\n", message);
  else
    perror(NULL);
}

void assert_error(const char *message) {
  prefix_error();
  ft_dprintf(STDERR_FILENO, "Assert error: %s\n", message);
  exit(ASSERT_ERROR_STATUS);
}

void	error_and_exit(const char *cmd, const char *message, int status)
{
	prefix_error();
	ft_dprintf(STDERR_FILENO, "%s: ", cmd);
	if (errno != 0)
		ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno));
	else
		ft_dprintf(STDERR_FILENO, "%s\n", message);
	exit(status);
}

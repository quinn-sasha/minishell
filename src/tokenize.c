#include "../include/minishell.h"

/*
blank
  A space or tab character.

control operator
  A token that performs a control function. It is a newline or '|'.

metacharacter
  A character that, when unquoted, separates words. A metacharacter is
  a space, tab, newline, or one of the following characters: ‘|’, ‘<’, or ‘>’.

token
  A sequence of characters considered a single unit by the shell.
  It is either a word or an operator.

operator
  A control operator or a redirection operator. See Redirections, for a list of
  redirection operators. Operators contain at least one unquoted metacharacter.

word
  A sequence of characters treated as a unit by the shell.
  Words may not include unquoted metacharacters.
*/

int is_blank(int c) {
  if (c == ' ' || c == '\t')
    return TRUE;
  return FALSE;
}

int is_metacharacter(int c) {

}

t_token *tokenize(char *input) {
  t_token head;
  t_token *token = &head;

  while (*input) {
    if (is_blank(input)) {
      input++;
      continue;
    }
    if ()
  }

}

#include "../include/minishell.h"

/*
blank is space or tab from the definition
https://www.gnu.org/software/bash/manual/bash.html#Definitions-1
*/
int is_blank(int c) {
  if (c == ' ' || c == '\t')
    return TRUE;
  return FALSE;
}

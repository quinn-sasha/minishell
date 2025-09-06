#include "../include/minishell.h"

int is_blank(int c) {
  if (c == ' ' || c == '\t')
    return TRUE;
  return FALSE;
}

#include "minishell.h"

bool is_default_ifs(int c) {
  if (c == ' ')
    return true;
  if (c == '\t')
    return true;
  if (c == '\n')
    return true;
  return false;
}

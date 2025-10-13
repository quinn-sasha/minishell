#include "minishell.h"

bool is_alpha_underscore(int c) {
  return ft_isalpha(c) || c == '_';
}

bool is_alpha_underscore_num(int c) {
  return is_alpha_underscore(c) || ft_isdigit(c);
}

bool is_identifier(const char *s) {
  if (s == NULL) {
    return false;
  }
  if (!is_alpha_underscore(*s)) {
    return false;
  }
  while (*s) {
    if (!is_alpha_underscore_num(*s)) {
      return false;
    }
    s++;
  }
  return true;
}


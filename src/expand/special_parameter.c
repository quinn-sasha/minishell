#include "minishell.h"

bool is_special_parameter(const char *s) {
  return s[0] == '$' && s[1] == '?';
}

void append_num_to_string(char **dest, unsigned int num) {
  if (num < 10) {
    append_character(dest, num + '0');
    return;
  }
  char *converted = unsigned_itoa(num, 10);
  int i = 0;
  while (converted[i]) {
    append_character(dest, converted[i]);
    i++;
  }
}

void expand_special_parameter(char **new_word, char **iter_to_return, char *iter, int last_status) {
  if (last_status < 0)
    assert_error("last status should not be negative");
  append_num_to_string(new_word, last_status);
  iter += 2;
  *iter_to_return = iter;
}

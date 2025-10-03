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

void expand_special_parameter(char **new_word, char **char_ptr_to_return, char *char_ptr, int last_status) {
  if (last_status < 0)
    assert_error("last status should not be negative");
  append_num_to_string(new_word, last_status);
  char_ptr += 2;
  *char_ptr_to_return = char_ptr;
}

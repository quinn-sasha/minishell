#include "test_expand.h"

int main(void) {
  printf("Test expand_shell_parameter() ... \n");
  test_append_character();
  test_expand_shell_parameter();
  printf("Test split_words() ... \n");
  test_split_words();
  printf("Test remove_quote() ... \n");
  test_remove_quote();
}

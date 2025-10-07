#include "test_expand.h"

int main(void) {
  printf("Test expand_shell_parameter() ... \n");
  test_expand_shell_parameter();
  printf("Test split_words() ... \n");
  test_split_words();
}

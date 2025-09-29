#include "test_expand.h"

void test_append_to_null(void) {
  char *string = NULL;
  int c = 'a';
  append_character(&string, c);
  assert(strcmp("a", string) == 0);
  free(string);
}

void test_append_to_normal_string(void) {
  char *expected = "Your success is inevitable";
  char *s = "Your success is inevitabl";
  int c = 'e';
  append_character(&s, c);
  assert(strcmp(expected, s) == 0);
  free(s);
}

void test_append_ten_times(void) {
  char *expected = "aaaaaaaaaa";
  char *s = NULL;
  int c = 'a';
  for (size_t i = 0; i < ft_strlen(expected); i++) {
    append_character(&s, c);
  }
  assert(strcmp(expected, s) == 0);
}

int main(void) {
  test_append_to_null();
  test_append_to_normal_string();
  test_append_ten_times();
}


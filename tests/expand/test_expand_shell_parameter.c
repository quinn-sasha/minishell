#include "test_expand.h"

/*
このコマンドがすでに実行されているという前提で、テストが行われます.
export HELLO="hello world\n"
*/

void assert_same_string(const char *s1, const char *s2) {
  assert(strcmp(s1, s2) == 0);
}

void test_simple_expansion(void) {
  printf("Test 'echo $HELLO' ... ");
  t_map *envmap = init_environment();
  int status;
  char *input = "echo $HELLO";
  t_token *token = tokenize(input, &status);
  t_simple_command *command = NULL;
  parse(&command, token);
  expand(command, envmap);
  printf("after expand");

  t_token *iter = command->arguments;
  assert_same_string(iter->word, "echo");
  iter = iter->next;
  assert_same_string(iter->word, "hello world\n");
  clean_command(&command);
  clean_environment(envmap);
  printf("PASS\n");
}

int main(void) {
  test_append_character();
  test_simple_expansion();
}

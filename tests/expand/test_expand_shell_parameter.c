#include "test_expand.h"

/*
このコマンドがすでに実行されているという前提で、テストが行われます.
export HELLO="hello world"
export NESTED_QUOTE="'$HOME'"
*/

void assert_same_string(const char *s1, const char *s2) {
  if (s1 == NULL && s2 == NULL)
    return;
  if (s1 == NULL)
    exit(EXIT_FAILURE);
  if (s2 == NULL)
    exit(EXIT_FAILURE);
  assert(strcmp(s1, s2) == 0);
}

static void test_simple_expansion(void) {
  printf("Test '$HELLO' ... ");
  t_map *envmap = init_environment();
  int status;
  char *input = "$HELLO";
  t_token *token = tokenize(input, &status);
  t_simple_command *command = NULL;
  parse(&command, token);
  expand_shell_parameter(command, envmap);

  t_token *iter = command->arguments;
  assert_same_string(iter->word, getenv("HELLO"));
  clean_command(&command);
  clean_environment(envmap);
  printf("PASS\n");
}

static void test_special_parameter_expansion(void) {
  printf("Test '$?' ... ");
  t_map *envmap = init_environment();
  envmap->last_status = 127;
  int status;
  char *input = "$?";
  t_token *token = tokenize(input, &status);
  t_simple_command *command = NULL;
  parse(&command, token);
  expand_shell_parameter(command, envmap);

  t_token *iter = command->arguments;
  assert_same_string(iter->word, "127");
  clean_command(&command);
  clean_environment(envmap);
  printf("PASS\n");
}

static void test_pipe_expansion(void) {
  printf("Test 'echo $HOME | cat $PWD' ... ");
  t_map *envmap = init_environment();
  int status;
  char *input = "echo $HOME | cat $PWD";
  t_token *token = tokenize(input, &status);
  t_simple_command *command = NULL;
  parse(&command, token);
  expand_shell_parameter(command, envmap);

  t_simple_command *node = command;
  t_token *arg = node->arguments;
  assert_same_string(arg->word, "echo");
  arg = arg->next;
  assert_same_string(arg->word, getenv("HOME"));
  node = node->next;
  arg = node->arguments;
  assert_same_string(arg->word, "cat");
  arg = arg->next;
  assert_same_string(arg->word, getenv("PWD"));

  clean_command(&command);
  clean_environment(envmap);
  printf("PASS\n");
}

static void test_non_existing_variable(void) {
  printf("Test '$100abc ... ");
  t_map *envmap = init_environment();
  int status;
  char *input = "$100abc";
  t_token *token = tokenize(input, &status);
  t_simple_command *command = NULL;
  parse(&command, token);
  expand_shell_parameter(command, envmap);

  t_simple_command *node = command;
  t_token *arg = node->arguments;
  assert_same_string(arg->word, "$100abc");

  clean_command(&command);
  clean_environment(envmap);
  printf("PASS\n");
}

static void test_redirect_expansion(void) {
  printf("Test 'echo hello >> $HELLO' ... ");
  t_map *envmap = init_environment();
  int status;
  char *input = "echo hello >> $HELLO";
  t_token *token = tokenize(input, &status);
  t_simple_command *command = NULL;
  parse(&command, token);
  expand_shell_parameter(command, envmap);

  t_simple_command *node = command;
  assert_same_string(node->redirect->to.filename, getenv("HELLO"));

  clean_command(&command);
  clean_environment(envmap);
  printf("PASS\n");
}

// TODO: this test can be only done as squinn in 42 school pc
// static void test_nested_quote(void) {
//   printf("Test nested quote variable ... ");
//   t_map *envmap = init_environment();
//   int status;
//   char *input = "$NESTED_QUOTE";
//   t_token *token = tokenize(input, &status);
//   t_simple_command *command = NULL;
//   parse(&command, token);
//   expand_shell_parameter(command, envmap);

//   t_simple_command *node = command;
//   t_token *arg = node->arguments;
//   assert_same_string(arg->word, "'/home/squinn'");
//   clean_command(&command);
//   clean_environment(envmap);
//   printf("PASS\n");
// }

void test_expand_shell_parameter() {
  test_append_character();
  test_simple_expansion();
  test_special_parameter_expansion();
  test_pipe_expansion();
  test_non_existing_variable();
  test_redirect_expansion();
  // test_nested_quote(); This test is problematic, so not execute this for now
}

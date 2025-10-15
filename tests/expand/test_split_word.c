#include "test_expand.h"

/*
このコマンドがすでに実行されているという前提で、テストが行われます.
export HELLO="hello world"
export SPACES="      "
export THREE_WORDS="kiss me baby"
*/

static void test_simple_expansion(void) {
  printf("Test '$HELLO' ... ");
  t_map *envmap = init_environment();
  char input[] = "$HELLO";
  t_token *token = tokenize(input);
  t_simple_command *command = NULL;
  parse(&command, token);
  expand_shell_parameter(command, envmap);
  if (!is_valid_syntax_after_expansion(command->redirect)) {
    printf("This inpu is valid, but is_valid_syntax_after_expansion() says wrong\n");
    exit(EXIT_FAILURE);
  }
  split_words(command);

  t_token *iter = command->arguments;
  assert_same_string(iter->word, "hello");
  iter = iter->next;
  assert_same_string(iter->word, "world");
  clean_command(&command);
  clean_environment(envmap);
  printf("PASS\n");
}

void test_special_parameter_expansion(void) {
  printf("Test '$?' ... ");
  t_map *envmap = init_environment();
  envmap->last_status = 127;
  char input[] = "$?";
  t_token *token = tokenize(input);
  t_simple_command *command = NULL;
  parse(&command, token);
  expand_shell_parameter(command, envmap);
  split_words(command);

  t_token *iter = command->arguments;
  assert_same_string(iter->word, "127");
  clean_command(&command);
  clean_environment(envmap);
  printf("PASS\n");
}

void test_spaces_variable_expansion(void) {
  printf("Test '$SPACES' ... ");
  t_map *envmap = init_environment();
  char input[] = "$SPACES";
  t_token *token = tokenize(input);
  t_simple_command *command = NULL;
  parse(&command, token);
  expand_shell_parameter(command, envmap);
  split_words(command);

  t_token *iter = command->arguments;
  if (!at_eof(iter)) {
    printf("This argument should be removed, but was not removed\n");
    exit(EXIT_FAILURE);
  }
  clean_command(&command);
  clean_environment(envmap);
  printf("PASS\n");
}

void test_quoted_spaces_variable_expansion(void) {
  printf("Test '\"$SPACES\"' ... ");
  t_map *envmap = init_environment();
  char input[] = "\"$SPACES\"";
  t_token *token = tokenize(input);
  t_simple_command *command = NULL;
  parse(&command, token);
  expand_shell_parameter(command, envmap);
  split_words(command);

  t_token *iter = command->arguments;
  assert_same_string(iter->word, "\x02""      ""\x02");  // (char)0x02 is DOUBLE_QUOTE_MARKER
  clean_command(&command);
  clean_environment(envmap);
  printf("PASS\n");
}

void test_invalid_syntax_after_expansion1(void) {
  printf("Test 'cat < $HELLO' ... ");
  t_map *envmap = init_environment();
  char input[] = "cat < $HELLO";
  t_token *token = tokenize(input);
  t_simple_command *command = NULL;
  parse(&command, token);
  expand_shell_parameter(command, envmap);
  if (is_valid_syntax_after_expansion(command->redirect)) {
    printf("This input should be ambiguous_redirect_error\n");
    exit(EXIT_FAILURE);
  }

  clean_command(&command);
  clean_environment(envmap);
  printf("PASS\n");
}

void test_invalid_syntax_after_expansion2(void) {
  printf("Test 'cat < $abc' ... ");
  t_map *envmap = init_environment();
  char input[] = "cat < $abc";
  t_token *token = tokenize(input);
  t_simple_command *command = NULL;
  parse(&command, token);
  expand_shell_parameter(command, envmap);
  if (is_valid_syntax_after_expansion(command->redirect)) {
    printf("This input should be ambiguous_redirect_error\n");
    exit(EXIT_FAILURE);
  }

  clean_command(&command);
  clean_environment(envmap);
  printf("PASS\n");
}

void test_three_words_expansion(void) {
  printf("Test 'THREE_WORDS' ... ");
  t_map *envmap = init_environment();
  char input[] = "$THREE_WORDS";
  t_token *token = tokenize(input);
  t_simple_command *command = NULL;
  parse(&command, token);
  expand_shell_parameter(command, envmap);
  split_words(command);

  t_simple_command *node = command;
  t_token *arg = node->arguments;
  assert_same_string(arg->word, "kiss");
  arg = arg->next;
  assert_same_string(arg->word, "me");
  arg = arg->next;
  assert_same_string(arg->word, "baby");

  clean_command(&command);
  clean_environment(envmap);
  printf("PASS\n");
}

void test_split_words() {
  test_simple_expansion();
  test_special_parameter_expansion();
  test_spaces_variable_expansion();
  test_quoted_spaces_variable_expansion();
  test_invalid_syntax_after_expansion1();
  test_invalid_syntax_after_expansion2();
  test_three_words_expansion();
}

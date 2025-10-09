#include "test_expand.h"

/*
以下のコマンドが実行されていることを前提としてテストする:
	export HELLO="hello world"
	export SPACES="      "
	export THREE_WORDS="kiss me baby"
	export QUOTED_WORD='"quoted    word"'
*/

static void test_remove_quote_token(void) {
  printf("Test '$QUOTED_WORD \"another    word\"' ... ");
  t_map *envmap = init_environment();
  int status;
  char *input = "$QUOTED_WORD \"another    word\"";
  t_token *token = tokenize(input, &status);
  t_simple_command *command = NULL;
  parse(&command, token);
  expand_shell_parameter(command, envmap);
  split_words(command);
  remove_quote(command);

  t_token *iter = command->arguments;
  assert_same_string(iter->word, "\"quoted");
  iter = iter->next;
  assert_same_string(iter->word, "word\"");
  iter = iter->next;
  assert_same_string(iter->word, "another    word");

  clean_command(&command);
  clean_environment(envmap);
  printf("PASS\n");
}

static void test_remove_quote_redirect(void) {
  printf("Test 'cat < \"infile\"' ... ");
  t_map *envmap = init_environment();
  int status;
  char *input = "cat < \"infile\"";
  t_token *token = tokenize(input, &status);
  t_simple_command *command = NULL;
  parse(&command, token);
  expand_shell_parameter(command, envmap);
  split_words(command);
  remove_quote(command);

  t_redirect *redirect = command->redirect;
  char *filename = redirect->to.filename;
  assert_same_string(filename, "infile");

  clean_command(&command);
  clean_environment(envmap);
  printf("PASS\n");
}

void test_remove_quote(void) {
  test_remove_quote_token();
  test_remove_quote_redirect();
}

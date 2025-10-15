#include "test_parse.h"

// 期待値の構造体を作ってテストする方法だと、redirectを作る方法が
// 自作の関数を使う必要があるので、ここではredirectのテストはしない.
int main() {
  test_really_simple_command();
  test_empty_string();
  test_pipe_and_redirect();
}

void test_really_simple_command() {
  printf("Test simple command 'ls -l' ... ");
  char *input = "ls -l";
  t_token *token = tokenize(input);
  t_simple_command *command = NULL;
  if (parse(&command, token) == PARSE_SYNTAX_ERROR) {
    printf("FAIL: expected parse() returns PARSE_SUCCESS, but got PARSE_SYNTAX_ERROR\n");
    exit(EXIT_FAILURE);
  }
  char *strings[] = {"ls", "-l", NULL};
  t_simple_command *expected_command = make_expected_command(strings);
  if (!is_generated_commands_correct(command, expected_command)) {
    printf("FAIL: command arguments are wrong\n");
    exit(EXIT_FAILURE);
  }
  clean_command(&command);
  clean_command(&expected_command);
  printf("PASS\n");
}

void test_empty_string() {
  printf("Test empty string: '' ...  ");
  char *input = "";
  t_token *token = tokenize(input);
  t_simple_command *command = NULL;
  if (parse(&command, token) == PARSE_SYNTAX_ERROR) {
    printf("FAIL: expected parse() returns PARSE_SUCCESS, but got PARSE_SYNTAX_ERROR\n");
    exit(EXIT_FAILURE);
  }
  if (command != NULL) {
    printf("FAIL: expected command to be NULL\n");
    exit(EXIT_FAILURE);
  }
  clean_command(&command);
  printf("PASS\n");
}

void test_pipe_and_redirect() {
  printf("Test pipe and redirect: '<< END echo 'abc' | cat > outfile.txt' ...  ");
  char input[] = "<< END echo 'abc' | cat > outfile.txt";
  t_token *token = tokenize(input);
  t_simple_command *command;
  t_simple_command *expected;
  if (parse(&command, token) == PARSE_SYNTAX_ERROR) {
    printf("FAIL: expected parse() returns PARSE_SUCCESS, but got PARSE_SYNTAX_ERROR\n");
    exit(EXIT_FAILURE);
  }
  char *strings1[] = {"echo", "\x01""abc""\x01", NULL}; // \x01 is SINGLE_QUOTE_MARKER
  char *strings2[] = {"cat", NULL};
  expected = make_expected_command(strings1);
  expected->next = make_expected_command(strings2);
  if (!is_generated_commands_correct(command, expected)) {
    printf("FAIL: command arguments are wrong\n");
    exit(EXIT_FAILURE);
  }
  clean_command(&command);
  clean_command(&expected);
  printf("PASS\n");
}

bool assert_tokens_equal(t_token *token, t_token *expected_token) {
  while (TRUE) {
    if (at_eof(token) && at_eof(expected_token))
      break;
    if (at_eof(token)) {
      printf("FAIL: Token list is too short. Expected more tokens\n");
      return false;
    }
    if (at_eof(expected_token)) {
      printf("FAIL: Token is too long. Extra tokens found\n");
      return false;
    }
    if (token->token_kind != expected_token->token_kind) {
      printf("FAIL: Token kind is wrong\n");
      printf("Expectd [%d], but got [%d]\n", expected_token->token_kind, token->token_kind);
      return false;
    }
    if (strcmp(token->word, expected_token->word) != 0) {
      printf("FAIL: Token word is wrong.\n");
      printf("Expected: [%s], but got [%s]\n", expected_token->word, token->word);
      return false;
    }
    token = token->next;
    expected_token = expected_token->next;
  }
  return true;
}

// child pid のテストはまだ追加されていない
bool is_generated_commands_correct(t_simple_command *command, t_simple_command *expected_command) {
  while (TRUE) {
    if (command == NULL && expected_command == NULL) {
      return true;
    }
    if (command && expected_command == NULL) {
      printf("FAILED: command list is too long. Extra commands found.\n");
      return false;
    }
    if (command == NULL && expected_command) {
      printf("FAILED: command list is too short. Expected more tokens.\n");
      return false;
    }
    if (!assert_tokens_equal(command->arguments, expected_command->arguments)) {
      printf("FAILED: command argument is wrong\n");
      return false;
    }
    command = command->next;
    expected_command = expected_command->next;
  }
}

// パイプやリダイレクトを無視して、コマンドへの引数を作る
t_simple_command *make_expected_command(char **strings) {
  t_simple_command *command = xcalloc(1, sizeof(t_simple_command));
  t_token *token;
  for (int i = 0; strings[i]; i++) {
    token = new_token(TOKEN_WORD, xstrdup(strings[i]));
    append_token(&command->arguments, token);
  }
  token = new_token(TOKEN_EOF, NULL);
  append_token(&command->arguments, token);
  return command;
}

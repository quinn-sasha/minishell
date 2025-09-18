#include "test_parse.h"

// 期待値の構造体を作ってテストする方法だと、redirectを作る方法が
// 自作の関数を使う必要があるので、ここではredirectのテストはしない.
int main() {
  test_really_simple_command();
}

void test_really_simple_command() {
  printf("Test simple command 'ls -l' ... ");
  int status;
  char *input = "ls -l";
  t_token *token = tokenize(input, &status);
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

bool is_same_redirectee(t_redirectee redirectee1, t_redirectee redirectee2, int is_fd) {
  if (is_fd) {
    return redirectee1.fd == redirectee2.fd;
  }
  return strcmp(redirectee1.filename, redirectee2.filename) == 0;
}

bool is_redirect_correct(t_redirect *redirect, t_redirect *expected_redirect) {
  if (redirect == NULL && expected_redirect == NULL) {
    return true;
  }
  if (redirect && expected_redirect == NULL) {
    printf("FAIL: redirect list is too long. Extra redirects found.\n");
    return false;
  }
  if (redirect == NULL && expected_redirect) {
    printf("FAIL: redirect list is too short. Expected more redirects.\n");
    return false;
  }

  if (redirect->redirect_kind != expected_redirect->redirect_kind) {
    printf("FAIL: expected redirect type [%d], but got [%d]\n",
            expected_redirect->redirect_kind, redirect->redirect_kind);
    return false;
  }
  if (redirect->redirect_kind == r_reading_until) {
    if (strcmp(redirect->here_doc_eof, expected_redirect->here_doc_eof) != 0) {
      printf("FAIL: expected here doc eof [%s], but got [%s]", expected_redirect->here_doc_eof, redirect->here_doc_eof);
      return false;
    }
    return true;
  }
  if (redirect->open_flags != expected_redirect->open_flags) {
    printf("FAIL: open flags are wrong (Expected redirect kind: %d, acutal kind: %d)\n",
            expected_redirect->redirect_kind, redirect->redirect_kind);
    return false;
  }
  if (!is_same_redirectee(redirect->from, expected_redirect->from, TRUE)) {
    printf("FAIL: redirect source's fd is wrong.\n");
    printf("Expected fd [%d], but got [%d]", expected_redirect->from.fd, redirect->from.fd);
    return false;
  }
  if (!is_same_redirectee(redirect->to, expected_redirect->to, FALSE)) {
    printf("FAIL: redirect destination's filename is wrong.\n");
    printf("Expected filename [%s], but got [%s]", expected_redirect->to.filename, redirect->to.filename);
    return false;
  }
  return is_redirect_correct(redirect->next, expected_redirect->next);
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
    if (!is_redirect_correct(command->redirect, expected_command->redirect)) {
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

#include "test_tokenize.h"

int main(void) {
  test_simple_command();
  test_empty_string();
  test_blank();
  test_pipe_and_redirect();
  test_unclosed_quote();
  test_quote_concatenation();
}

void test_simple_command() {
  printf("Test simple command: 'ls -l' ...  ");
  char *input = "ls -l";
  t_expected_token expected[] = {
    {TOKEN_WORD, "ls"},
    {TOKEN_WORD, "-l"},
    {TOKEN_EOF, NULL}
  };
  t_token *token = tokenize(input);
  int result = assert_tokens_equal(token, expected, sizeof(expected) / sizeof(t_expected_token));
  if (result == false)
    exit(EXIT_FAILURE);
  free_token_list(token);
}

void test_empty_string() {
  printf("Test empty string: '' ...  ");
  char *input = "";
  t_expected_token expected[] = {
    {TOKEN_EOF, NULL}
  };
  t_token *token = tokenize(input);
  int result = assert_tokens_equal(token, expected, sizeof(expected) / sizeof(t_expected_token));
  if (result == false)
    exit(EXIT_FAILURE);
  free_token_list(token);
}

void test_blank() {
  printf("Test empty string: '    \t' ...  ");
  char *input = "    \t";
  t_expected_token expected[] = {
    {TOKEN_EOF, NULL}
  };
  t_token *token = tokenize(input);
  int result = assert_tokens_equal(token, expected, sizeof(expected) / sizeof(t_expected_token));
  if (result == false)
    exit(EXIT_FAILURE);
  free_token_list(token);
}

void test_pipe_and_redirect() {
  printf("Test pipe and redirect: '<< END echo 'abc' | cat > outfile.txt' ...  ");
  char *input = xstrdup("<< END echo 'abc' | cat > outfile.txt");
  t_expected_token expected[] = {
    {TOKEN_OPERATOR, "<<"},
    {TOKEN_WORD, "END"},
    {TOKEN_WORD, "echo"},
    {TOKEN_WORD, "\x01" "abc" "\x01"}, // \x01 is SINGLE_QUOTE_MARKER
    {TOKEN_OPERATOR, "|"},
    {TOKEN_WORD, "cat"},
    {TOKEN_OPERATOR, ">"},
    {TOKEN_WORD, "outfile.txt"},
    {TOKEN_EOF, NULL}
  };
  t_token *token = tokenize(input);

  int result = assert_tokens_equal(token, expected, sizeof(expected) / sizeof(t_expected_token));
  free(input);
  if (result == false)
    exit(EXIT_FAILURE);
  free_token_list(token);
}

void test_quote_concatenation() {
  printf("Test '\'$HOME\'\"$HOME\"' ...  ");
  char input[] = "\'$HOME\'\"$HOME\"";
  t_expected_token expected[] = {
    {TOKEN_WORD, "\x01" "$HOME" "\x01" "\x02" "$HOME" "\x02"}, // \x01 is SINGLE_QUOTE_MARKER
    {TOKEN_EOF, NULL}
  };
  t_token *token = tokenize(input);

  int result = assert_tokens_equal(token, expected, sizeof(expected) / sizeof(t_expected_token));
  if (result == false)
    exit(EXIT_FAILURE);
  free_token_list(token);
}

void test_unclosed_quote() {
  printf("Test: Unclosed Quote 'echo \"hello'... ");
  char *input = xstrdup("'echo \"hello");
  t_token *token = tokenize(input);
  free(input);
  if (token == NULL) {
    printf("PASS\n");
  }
  else {
    printf("FAIL: unclosed errro was not detected\n");
    exit(EXIT_FAILURE);
  }
}

bool assert_tokens_equal(t_token *token, t_expected_token *expected_tokens, int size) {
  t_token *iter = token;
  for (int i = 0; i < size; i++) {
    if (iter == NULL) {
      printf("FAIL: Token list is too short. Expected more tokens\n");
      return false;
    }
    if (iter->token_kind != expected_tokens[i].token_kind) {
      printf("FAIL: Token kind is wrong\n");
      printf("An error found at expected_tokens index: %d\n", i);
      return false;
    }
    if (iter->word == NULL && expected_tokens[i].word == NULL) {
      iter = iter->next;
      continue;
    }
    if (strcmp(iter->word, expected_tokens[i].word) != 0) {
      printf("FAIL: Token word is wrong.\n");
      printf("Expected: %s, but got %s\n", expected_tokens[i].word, iter->word);
      return false;
    }
    iter = iter->next;
  }
  if (iter != NULL) {
    printf("FAIL: Token is too long. Extra tokens found\n");
    return false;
  }
  printf("PASS\n");
  return true;
}


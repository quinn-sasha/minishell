#include "test_tokenize.h"

int main(void) {
  test_simple_command();
}

void test_simple_command() {
  printf("Test simple command: 'ls -l' ...\n");
  char *input = "ls -l";
  t_expected_token expected[] = {
    {TOKEN_WORD, "ls"},
    {TOKEN_WORD, "-l"},
    {TOKEN_EOF, NULL}
  };
  int status;
  t_token *token = tokenize(input, &status);
  int result = assert_tokens_equal(token, expected, sizeof(expected) / sizeof(t_expected_token));
  if (result == false)
    exit(EXIT_FAILURE);
  free_token(token);
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


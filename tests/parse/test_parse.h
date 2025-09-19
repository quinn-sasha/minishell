#include "../include/minishell.h"
#include <string.h>

bool assert_tokens_equal(t_token *token, t_token *expected_token);
bool is_generated_commands_correct(t_simple_command *command, t_simple_command *expected_command);
t_simple_command *make_expected_command(char **strings);
void test_really_simple_command();
void test_empty_string();
void test_pipe_and_redirect();

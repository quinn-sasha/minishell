#include "../include/minishell.h"

bool assert_tokens_equal(t_token *token, t_token *expected_token);
bool is_same_redirectee(t_redirectee redirectee1, t_redirectee redirectee2, int is_fd);
bool is_redirect_correct(t_redirect *redirect, t_redirect *expected_redirect);
bool is_generated_commands_correct(t_simple_command *command, t_simple_command *expected_command);
t_simple_command *make_expected_command(char **strings);
void test_really_simple_command();


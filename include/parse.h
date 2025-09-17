#ifndef PARSE_H
#define PARSE_H

#define PIPE_SYMBOL "|"

// redirect.c
void fill_redirect(t_redirect *redirect, t_redirect_kind r_kind ,t_token *token);
t_redirect *new_redirect(t_token *token);
void append_redirect(t_redirect **head, t_redirect *element);
// make_simple_command.h
void append_command_element(t_simple_command *command, t_token **token_to_return, t_token *token);
t_simple_command *make_simple_command(t_token **token_to_return, t_token *token);
t_simple_command *make_simple_command_list(t_token *token);
// parse.c
bool is_valid_syntax(t_token *token);
int parse(t_simple_command **command, t_token *token);

#endif

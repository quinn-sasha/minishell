#ifndef EXPAND_H
#define EXPAND_H

#include "parse.h"
#include "environ.h"

// special_parameter.c
bool is_special_parameter(const char *s);
void append_num_to_string(char **dest, unsigned int num);
void expand_special_parameter(char **new_word, char **iter_to_return, char *iter, int last_status);
// expand_shell_parameter.c
bool need_to_expand(char *word);
void expand_word(char **word);
void expand_token_words(t_token *token);
void expand_redirect_words(t_redirect *redirect);
void expand_shell_parameter(t_simple_command *command, t_map *envmap);
// expand.c
void append_character(char **string, int c);
int expand(t_simple_command *command, t_map *envmap);

#endif

#ifndef EXPAND_H
#define EXPAND_H

#include "parse.h"
#include "environ.h"

#define EXPAND_SUCCESS 0
#define EXPAND_SYNTAX_ERROR 1
// expand_word() return values
#define EXPANDED 0
#define NOT_EXPANDED 1

#define DEFAULT_IFS_CHARS " \t\n"

// special_parameter.c
bool is_special_parameter(const char *s);
void append_num_to_string(char **dest, unsigned int num);
void expand_special_parameter(char **new_word, char **iter_to_return, char *iter, int last_status);
// expand_shell_parameter.c
bool need_to_expand(char *word);
void expand_parameter(char **new_word, char **iter_to_return, char *iter, t_map *envmap);
int expand_word(char **word, t_map *envmap);
void expand_token_words(t_token *token, t_map *envmap);
void expand_redirect_words(t_redirect *redirect, t_map *envmap);
void expand_shell_parameter(t_simple_command *command, t_map *envmap);
// is_valid_syntax_after_expansion.c
bool is_valid_filename(const char *filename);
int is_valid_syntax_after_expansion(t_redirect *redirect);
// split_token_words.c
void split_token_word(t_token *token);
void split_token_words(t_token *token);
// word_splitting.c
void trim_redirect_filename(t_redirect *redirect);
void split_words(t_simple_command *command);
// remove_quote.c
void remove_quote_word(char **word);
void remove_quote_token(t_token *token);
void remove_quote_redirect(t_redirect *redirect);
void remove_quote(t_simple_command *command);
// expand.c
void append_character(char **string, int c);
void append_string_to_string(char **dest, char *src);
int expand(t_simple_command *command, t_map *envmap);

#endif

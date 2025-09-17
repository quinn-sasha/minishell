#ifndef TOKENIZE_H
#define TOKENIZE_H

#define TOKENIZE_SUCCESS 0
#define UNCLOSED_QUOTE_STATUS 1
#define PARSE_SUCCESS 0
#define PARSE_SYNTAX_ERROR 1

#define SINGLE_QUOTE_CHARCTER '\''
#define DOUBLE_QUOTE_CHARACTER '"'

#define UNCLOSED_QUOTE_ERROR "unclosed quote"

typedef enum e_token_kind t_token_kind;
typedef struct s_token t_token;

typedef enum e_token_kind {
  TOKEN_OPERATOR,
  TOKEN_WORD,
  TOKEN_EOF,
} t_token_kind;

struct s_token {
  char *word;
  t_token_kind token_kind;
  t_token *next;
};

// token.c
bool at_eof(t_token *token);
bool is_same_operator(t_token *token, char *operator);
t_token *new_token(t_token_kind token_kind, char *word);
t_token *duplicate_token(t_token *token);
void append_token(t_token **token, t_token *element);
// tokenize.c
int is_blank(int c);
int is_quote(int c);
int is_metacharacter(int c);
t_token *consume_operator(char **input_to_advance, char *input);
t_token *consume_quoted_word(char **input_to_advance, char *input, int *error_status);
t_token *consume_word(char **input_to_advance, char *input);
t_token *tokenize(char *input, int *error_status);

#endif

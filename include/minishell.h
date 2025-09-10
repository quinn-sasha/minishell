#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

#include "../libft/libft.h"

#define TRUE 1
#define SUCCESS 0
#define FAILED -1
#define CHILD 0

#define TOKENIZE_SUCCESS 0
#define UNCLOSED_QUOTE_STATUS 1
#define SINGLE_QUOTE_CHARCTER '\''
#define DOUBLE_QUOTE_CHARACTER '"'

#define COMMAND_NOT_FOUND_STATUS 127
#define PERMISSION_DENIED_STATUS 126


#define COMMAND_NOT_FOUND_ERROR "command not found"
#define PERMISSION_DENIED_ERROR "permission denied"
#define UNCLOSED_QUOTE_ERROR "unclosed quote"

typedef enum {
  TOKEN_OPERATOR,
  TOKEN_WORD,
  TOKEN_EOF,
} t_token_kind;

typedef struct s_word_list t_word_list;
typedef struct s_command t_command;
typedef struct s_token t_token;

struct s_word_list {
  struct s_word_list *next;
  char *word;
};

struct s_command {
  t_word_list *words;
};

struct s_token {
  char *word;
  t_token_kind token_kind;
  struct s_token *next;
};

// utils.c
// tokenize.c
int is_blank(int c);
int is_quote(int c);
int is_metacharacter(int c);
t_token *new_token(t_token_kind token_kind, char *word);
bool at_eof(t_token *token);
t_token *consume_operator(char **input_to_advance, char *input);
t_token *consume_quoted_word(char **input_to_advance, char *input, int *error_status);
t_token *consume_word(char **input_to_advance, char *input);
t_token *tokenize(char *input, int *error_status);
// parse.c
int is_blank(int c);
t_word_list *new_word_list(char *word);
char **convert_word_list_to_string_array(t_word_list *words);
int parse(char *input, t_command *command);
// destructor.c
void clean_command(t_command *command);
// exec.c
char *find_path(char *command_name);
void execute_command(t_command command);


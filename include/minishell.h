#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

#include "../libft/libft.h"
#include "xlibrary.h"

#define TRUE 1
#define SUCCESS 0
#define FAILED -1
#define CHILD 0

#define TOKENIZE_SUCCESS 0
#define UNCLOSED_QUOTE_STATUS 1
#define PARSE_SUCCESS 0
#define PARSE_SYNTAX_ERROR 1

#define SINGLE_QUOTE_CHARCTER '\''
#define DOUBLE_QUOTE_CHARACTER '"'
#define PIPE_SYMBOL "|"

#define COMMAND_NOT_FOUND_STATUS 127
#define PERMISSION_DENIED_STATUS 126

#define PREFIX_ERROR "micro-shell: "
#define COMMAND_NOT_FOUND_ERROR "command not found"
#define PERMISSION_DENIED_ERROR "permission denied"
#define UNCLOSED_QUOTE_ERROR "unclosed quote"

typedef enum e_token_kind t_token_kind;
typedef enum e_redirect_kind t_redirect_kind;
typedef union u_redirectee t_redirectee;
typedef struct s_token t_token;
typedef struct s_redirect t_redirect;
typedef struct s_simple_command t_simple_command;

typedef enum e_token_kind {
  TOKEN_OPERATOR,
  TOKEN_WORD,
  TOKEN_EOF,
} t_token_kind;

// r_reading_until == here document
typedef enum e_redirect_kind {
  r_input_direction,
  r_output_direction,
  r_appending_to,
  r_reading_until
} t_redirect_kind;

struct s_token {
  char *word;
  t_token_kind token_kind;
  t_token *next;
};

union u_redirectee {
  int fd;
  char *filename;
};

// e.g. > outfile
// from.fd is STDOUT_FILENO
// to.filename is outfile
struct s_redirect {
  t_redirect *next; // Next element or NULL
  int open_flags;
  t_redirectee from;
  t_redirectee to;
  t_redirect_kind redirect_kind;
  char *here_doc_eof;
};

struct s_simple_command {
  struct s_simple_command *next; // Next element or NULL
  t_token *arguments;
  t_redirect *redirect;
  pid_t child_pid;
};

// error.c
void prefix_error(void);
void syntax_error(const char *unexpected_token);
void fatal_error(const char *message);
// token.c
bool at_eof(t_token *token);
bool is_same_operator(t_token *token, char *operator);
t_token *new_token(t_token_kind token_kind, char *word);
// tokenize.c
int is_blank(int c);
int is_quote(int c);
int is_metacharacter(int c);
t_token *consume_operator(char **input_to_advance, char *input);
t_token *consume_quoted_word(char **input_to_advance, char *input, int *error_status);
t_token *consume_word(char **input_to_advance, char *input);
t_token *tokenize(char *input, int *error_status);
// parse.c
// destructor.c
void free_token(t_token *token);
// exec.c
char *find_path(char *command_name);


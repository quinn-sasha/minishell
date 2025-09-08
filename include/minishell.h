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
#define SINGLE_QUOTE_ERROR 1

#define COMMAND_NOT_FOUND_ERROR "command not found"
#define PERMISSION_DENIED_ERROR "permission denied"

#define COMMAND_NOT_FOUND_STATUS 127
#define PERMISSION_DENIED_STATUS 126

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


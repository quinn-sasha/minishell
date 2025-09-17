#ifndef PARSE_H
#define PARSE_H

#define PIPE_SYMBOL "|"

typedef struct s_redirect t_redirect;
typedef struct s_simple_command t_simple_command;
typedef enum e_redirect_kind t_redirect_kind;
typedef union u_redirectee t_redirectee;

// r_reading_until == here document
typedef enum e_redirect_kind {
  r_input_direction,
  r_output_direction,
  r_appending_to,
  r_reading_until
} t_redirect_kind;

// redirect.from is always fd
// redirect.to is always filename
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

// redirect.c
void fill_redirect(t_redirect *redirect, t_redirect_kind r_kind ,t_token *token);
t_redirect *new_redirect(t_token *token);
void append_redirect(t_redirect **head, t_redirect *element);
// make_simple_command.c
void append_command_element(t_simple_command *command, t_token **token_to_return, t_token *token);
t_simple_command *make_simple_command(t_token **token_to_return, t_token *token);
t_simple_command *make_simple_command_list(t_token *token);
// parse.c
bool is_valid_syntax(t_token *token);
int parse(t_simple_command **command, t_token *token);

#endif

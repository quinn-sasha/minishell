#ifndef COMMAND_H
#define COMMAND_H

typedef struct s_redirect t_redirect;
typedef struct s_simple_command t_simple_command;

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

#endif

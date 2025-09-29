#ifndef MINISHELL_H
#define MINISHELL_H

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <signal.h>
#if defined(__linux__)
#include <linux/limits.h>
#else
#define PATH_MAX 4096
#endif

#include "../libft/libft.h"
#include "error.h"
#include "signal_handler.h"
#include "environ.h"
#include "xlibrary.h"
#include "tokenize.h"
#include "parse.h"
#include "expand.h"

#define TRUE 1
#define SUCCESS 0
#define FAILED -1
#define CHILD 0

#define COMMAND_NOT_FOUND_STATUS 127
#define PERMISSION_DENIED_STATUS 126

#define COMMAND_NOT_FOUND_ERROR "command not found"
#define PERMISSION_DENIED_ERROR "permission denied"

// destructor.c
void free_token(t_token *token);
void clean_redirect(t_redirect *redirect);
void clean_environment(t_map *envmap);
void clean_command(t_simple_command **command);
// exec.c
char *find_path(char *command_name);

#endif

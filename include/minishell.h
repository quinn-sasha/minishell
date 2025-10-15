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
#endif
#ifndef PATH_MAX
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
#include "redirect.h"

#define TRUE 1
#define SUCCESS 0
#define FAILED -1
#define CHILD 0
#define READ 0
#define WRITE 1

// utils.c
char	*unsigned_itoa(unsigned long long num, unsigned int base);
int count_words(const char *s, const char *excluded_chars);
// destructor.c
void free_token_list(t_token *token);
void clean_redirect(t_redirect *redirect);
void clean_environment(t_map *envmap);
void clean_command(t_simple_command **command);
// exec.c
char *find_path(char *command_name);

#endif

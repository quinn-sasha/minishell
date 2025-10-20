/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:05:30 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 15:05:11 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# if defined(__linux__)
#  include <linux/limits.h>
# endif
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# include "../libft/libft.h"
# include "xlibrary.h"
# include "environ.h"
# include "signal_handler.h"
# include "error.h"
# include "tokenize.h"
# include "expand.h"
# include "redirect.h"
# include "parse.h"
# include "exec.h"
# include "builtin.h"

# define TRUE 1
# define SUCCESS 0
# define FAILED -1
# define CHILD 0
# define READ 0
# define WRITE 1
# define SYNTAX_ERROR_LAST_STATUS 2

// utils_string.c
char	*unsigned_itoa(unsigned long long num, unsigned int base);
size_t	count_array(char **array);
void	free_array(char **array);
char	*join_str_separator(const char *s1, const char *s2, char sep);

// utils_word.c
int		count_words(char *s, const char *excluded_chars);

// destructor.c
void	free_token_list(t_token *token);
void	clean_redirect(t_redirect *redirect);
void	clean_environment(t_map *envmap);
void	clean_command(t_simple_command **command);

#endif

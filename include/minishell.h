/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:28:02 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/03 11:51:01 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h> // printf, perror
#include <stdlib.h> // malloc, free, exit, getenv
#include <unistd.h> // write, read, close, pipe, dup, dup2
#include <fcntl.h> //access, open
#include <sys/stat.h> // stat, lstat, fstat
#include <unistd.h> // unlink, execve, getcwd, chdir, isatty, ttyname, ttyslot
#include <dirent.h> // opendir, readdir, closedir
#include <sys/wait.h> // fork, wait, waitpid, wait3, wait4
#include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill
#include <string.h> //strerror
#include <sys/ioctl.h> // ioctl
#include <termios.h> // tcsetattr, tcgetattr
#include <termcap.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

// builtin.c
int		check_builtin(const char *input);
int		is_separator(char c);
int		is_builtin(const char *input, const char *cmd);
int		builtin_pwd(void);
int		builtin_exit(void);

// just_for_debug.c
void	print_str_array(char **arr);

// parser.c
int		is_pipe(char c);
int		count_pipes(const char *input);
int		split_pipe_loop(const char *input, char **res);
int		split_by_pipe(const char *input, char ***commands, int *num_cmd);

// utils.c
void	free_str_array(char **arr);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
int		ft_strndup(const char *s, size_t n, char **dest);

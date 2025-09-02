/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:28:02 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/01 21:10:50 by yurishik         ###   ########.fr       */
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
int	builtin_pwd(void);

// utils.c
int	ft_strcmp(const char *s1, const char *s2);

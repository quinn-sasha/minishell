/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:28:02 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/08 09:28:57 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h> // printf, perror
# include <stdlib.h> // malloc, free, exit, getenv
# include <unistd.h> // write, read, close, pipe, dup, dup2
# include <fcntl.h> //access, open
# include <sys/stat.h> // stat, lstat, fstat
# include <unistd.h> // unlink, execve, getcwd, chdir, isatty, ttyname, ttyslot
# include <dirent.h> // opendir, readdir, closedir
# include <sys/wait.h> // fork, wait, waitpid, wait3, wait4
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill
# include <string.h> //strerror
# include <sys/ioctl.h> // ioctl
# include <termios.h> // tcsetattr, tcgetattr
# include <termcap.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

# define STD_ERR 2
# define SUCCESS 0
# define FAILURE 1
# define FLG_TRUE 1
# define FLG_FALSE 0

typedef struct s_environ
{
	char	**env;
	int		last_status;
}	t_environ;

// builtin.c
int		check_builtin(const char *input);
int		is_builtin(const char *input, const char *cmd);
int		builtin_pwd(void);
int		builtin_exit(void);

// env.c
int		get_env_size(char **env);
int		copy_env(char ***dest, char **environ);
int		initialize_environ(t_environ *env, char **environ);
int		find_env_key(t_environ *env, const char *key);
int		unset_env(t_environ *env, const char *name);

// execute_command.c
void	print_command_not_found(const char *cmd);
int		make_full_path(const char *dir, const char *cmd, char **full_path);
int		try_exec_paths(char **tokens, char **envp, char *path_env);
void	execute_command(char **tokens, char **envp);

// just_for_debug.c
void	print_str_array(char **arr);

// parser_pipe.c
int		is_pipe(char c);
int		count_pipes(const char *input);
int		split_pipe_loop(const char *input, char **res);
int		split_by_pipe(const char *input, char ***commands, int *num_cmd);

// parser_separator.c
int		is_separator(char c);
int		count_tokens(char *input);
int		split_separator_loop(const char *input, char **res);
int		split_by_separator(const char *input, char ***result);

// utils.c
void	free_str_array(char **arr);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
int		ft_strndup(const char *s, size_t n, char **dest);

#endif

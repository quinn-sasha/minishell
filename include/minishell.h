/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:28:02 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/16 16:49:49 by yurishik         ###   ########.fr       */
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// builtin.c
int		check_builtin(const char *input);
int		is_builtin(const char *input, const char *cmd);
int		builtin_pwd(void);
int		builtin_exit(void);

// env.c
int		initialize_environ(t_env **dest, char **environ);
char	*find_env(t_env *head, const char *key);
int		is_env_key_name(const char *name);
void	unset_mid_node(t_env *prev, t_env *current);
int		unset_env(t_env **head, const char *name);

// env_utils.c
int		get_key_length(char *str);

// execute_command.c
int		set_full_path(const char *dir, const char *cmd, char **full_path);
int		make_full_path(const char *dir, const char *cmd, char **full_path);
int		check_and_exec(char *dir, char **tokens, char **envp);
int		try_exec_paths(char **tokens, char **envp, char *path_env);
void	execute_command(char **tokens, char **envp);

// handle_env_list.c
t_env	*env_lstnew(char *str);
void	env_lstadd_back(t_env **lst, t_env *new);
void	env_lstfree(t_env *head);
void	env_delone(t_env *lst);

// just_for_debug.c
void	print_str_array(char **arr);
void	print_env(t_env *head);

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

// utils2.c
void	print_command_not_found(const char *cmd);

#endif

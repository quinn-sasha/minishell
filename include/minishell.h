/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:28:02 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/02 15:59:42 by yurishik         ###   ########.fr       */
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

typedef struct s_env			t_env;
typedef enum e_token_kind		t_token_kind;
typedef enum e_redirect_kind	t_redirect_kind;
typedef union u_redirectee		t_redirectee;
typedef struct s_token			t_token;
typedef struct s_redirect		t_redirect;
typedef struct s_simple_command	t_simple_command;

struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
};

typedef enum e_token_kind
{
	TOKEN_OPERATOR,
	TOKEN_WORD,
	TOKEN_EOF,
}	t_token_kind;

typedef enum e_redirect_kind
{
	r_input_direction,
	r_output_direction,
	r_appending_to,
	r_reading_until
}	t_redirect_kind;

struct s_token
{
	char			*word;
	t_token_kind	token_kind;
	t_token			*next;
};

union u_redirectee
{
	int		fd;
	char	*filename;
};

struct s_redirect
{
	t_redirect			*next;
	int					open_flags;
	t_redirectee		from;
	t_redirectee		to;
	t_redirect_kind		redirect_kind;
	char				*here_doc_eof;
};

struct s_simple_command
{
	struct s_simple_command	*next;
	t_token					*arguments;
	t_redirect				*redirect;
	pid_t					child_pid;
};

// builtin.c
int		check_builtin(char *input);
int		is_builtin(const char *input, const char *cmd);

// builtin_exit.c
int		builtin_exit(char **tokens);

// builtin_export.c
char	*get_key(char *str);
char	*get_value(char *str);
t_env	*env_lstempty(char *key);
int		set_empty_export(t_env **env, char *str);
int		builtin_export(t_env **env, char *str);

// builtin_pwd.c
int		builtin_pwd(void);

// builtin_unset.c
void	unset_mid_node(t_env *prev, t_env *current);
int		builtin_unset(t_env **head, const char *name);

// env.c
int		initialize_environ(t_env **dest, char **environ);
char	*find_env(t_env *head, const char *key);
int		update_env(t_env **head, char *key, char *value);

// env_utils.c
int		get_key_length(char *str);

// expand_env.c
int		is_env_key_first_char(char c);
int		is_env_key_char(char c);
int		is_env_key_name(const char *name);

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
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
char	*ft_strchr(const char *s, int c);

#endif

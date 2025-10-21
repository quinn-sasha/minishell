/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:46:02 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/21 17:16:09 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <errno.h>
# include <sys/stat.h>

// empty_args.c
int		is_command_args_empty(t_simple_command *command);
void	execute_empty_command(t_simple_command *command);

// exec.c
char	**tokens_to_argv(t_token *token);
void	validate_access(char *path, char *cmd);
void	exec_nonbuiltin(t_simple_command *command, t_map *envmap);
int		exec(t_simple_command *command, t_map *envmap);

// heredoc.c
int		stop_readline_if_sigint(void);
char	*expand_heredoc_line(char *line, t_map *envmap);
int		read_heredoc(const char *delimiter, bool is_quoted, t_map *envmap);

// path.c
char	*search_path_mode(const char *filename, int mode, t_map *envmap);
char	*search_path(const char *filename, t_map *envmap);
int		set_path_cd(char *path, char *pwd, char **argv, t_map *envmap);

// pipe.c
void	prepare_pipe(t_simple_command *command);
void	prepare_pipe_child(t_simple_command *command);
void	prepare_pipe_parent(t_simple_command *command);
int		wait_pipe(pid_t last_pid);
pid_t	exec_pipe(t_simple_command *command, t_map *envmap);

// redirect.c
int		gather_heredoc(t_simple_command *command, t_map *envmap);
int		open_fd(t_redirect *redirect);
int		open_redirect_file(t_redirect *redirect);
void	do_redirect(t_redirect *redirect);
void	reset_redirect(t_redirect *redirect);

// read_until_delimiter
# define HEREDOC_INTERRUPTED 1
# define HEREDOC_FINISHED 0

#endif

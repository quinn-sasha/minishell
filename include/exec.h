/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:46:02 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/07 16:25:50 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <errno.h>
# include <sys/stat.h>

char	**get_envmap(t_map *envmap);
size_t	count_map_item(t_map *envmap);

void	do_redirect(t_redirect *redirect);
void	reset_redirect(t_redirect *redirect);

char	**tokens_to_argv(t_token *token);
size_t	count_token(t_token *token);
char	*search_path_mode(const char *filename, int mode, t_map *envmap);
char	*search_path(const char *filename, t_map *envmap);
void	validate_access(char *path, char *cmd);
void	exec_nonbuiltin(t_simple_command *command, t_map *envmap);
pid_t	exec_pipe(t_simple_command *command, t_map *envmap);
int		exec(t_simple_command *command, t_map *envmap);

int		is_builtin(void);
int		exec_builtin(t_simple_command *command, t_map *envmap);

int		wait_pipe(pid_t last_pid);
void	error_and_exit(const char *cmd, const char *message, int status);
void	free_array(char **array);

void	reset_signal(int signum);

void	prepare_pipe(t_simple_command *command);
void	prepare_pipe_child(t_simple_command *command);
void	prepare_pipe_parent(t_simple_command *command);

#endif

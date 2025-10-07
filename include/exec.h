/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:46:02 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/07 17:12:53 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <errno.h>
# include <sys/stat.h>

// exec.c
char	**tokens_to_argv(t_token *token);
void	validate_access(char *path, char *cmd);
void	exec_nonbuiltin(t_simple_command *command, t_map *envmap);
int		exec(t_simple_command *command, t_map *envmap);

// path.c
char	*search_path_mode(const char *filename, int mode, t_map *envmap);
char	*search_path(const char *filename, t_map *envmap);

// pipe.c
void	prepare_pipe(t_simple_command *command);
void	prepare_pipe_child(t_simple_command *command);
void	prepare_pipe_parent(t_simple_command *command);
int		wait_pipe(pid_t last_pid);
pid_t	exec_pipe(t_simple_command *command, t_map *envmap);

// redirect.c
void	do_redirect(t_redirect *redirect);
void	reset_redirect(t_redirect *redirect);

#endif

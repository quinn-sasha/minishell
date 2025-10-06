/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:46:02 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/06 15:57:02 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

#include <errno.h>
#include <sys/stat.h>

char    **get_envmap(t_map *envmap);
size_t  count_map_item(t_map *envmap);

char    *search_path_mode(const char *filename, int mode, t_map *envmap);
char    *search_path(const char *filename, t_map *envmap);

char    **tokens_to_argv(t_token *token);
void    validate_access(char *path, char *cmd);
void    error_and_exit(const char *cmd, const char *message, int status);
void    exec_nonbuiltin(t_simple_command *command, t_map *envmap);

int     wait_pipe(pid_t last_pid);
int     exec(t_simple_command *command, t_map *envmap);

#endif

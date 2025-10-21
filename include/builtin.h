/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:37:36 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/21 17:10:28 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

// builtin.c
int		exec_builtin(t_simple_command *command, t_map *envmap);
int		is_builtin(t_simple_command *command);

// builtin_cd.c
void	process_path(char **compressed_array, const char *part, size_t *j);
char	**compress_path_array(char **path_array);
char	*create_final_path(char **path_array);
char	*resolve_pwd(char *pwd, char *path);
int		builtin_cd(char **argv, t_map *envmap);

// builtin_echo.c
int		is_n_option(char *str);
int		builtin_echo(char **argv);

// builtin_env.c
int		builtin_env(t_map *envmap);

// builtin_exit.c
int		is_numeric(const char *str);
long	string_to_long(char *str, char **ptr);
void	builtin_argv_check(char **argv, t_map *envmap);
int		builtin_exit(char **argv, t_map *envmap);

// builtin_export_sorting.c
t_item	**extract_items_to_array(t_map *envmap, size_t count);
void	bubble_sort_items(t_item **array, size_t count);
t_item	**map_sort(t_map *envmap);
int		display_map_ordered(t_map *envmap);

// builtin_export.c
char	*create_export_string(char *name, char *value, t_map *envmap);
int		free_and_return_status(char *name, char *value, int status);
int		process_export_argument(char *arg, t_map *envmap);
int		builtin_export(char **argv, t_map *envmap);

// builtin_pwd.c
int		builtin_pwd(void);

// builtin_unset.c
int		builtin_unset(char **argv, t_map *envmap);

#endif

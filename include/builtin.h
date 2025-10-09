/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:37:36 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/09 16:18:00 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int	is_builtin(t_simple_command *command);
int	exec_builtin(t_simple_command *command, t_map *envmap);
int	builtin_unset(char **argv, t_map *envmap);
int builtin_env(t_map *envmap);

#endif

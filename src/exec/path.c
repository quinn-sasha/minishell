/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:00:20 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/07 17:00:26 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_path_mode(const char *filename, int mode, t_map *envmap)
{
	char	*envpath;
	char	**paths;
	char	*full_cmd_path;
	int		i;

	envpath = xgetenv(envmap, "PATH");
	if (!envpath)
		return (NULL);
	paths = ft_split(envpath, ':');
	if (!paths)
		fatal_error("malloc");
	i = 0;
	while (paths[i])
	{
		full_cmd_path = join_str_separator(paths[i], filename, '/');
		if (access(full_cmd_path, mode) == SUCCESS)
		{
			free_array(paths);
			return (full_cmd_path);
		}
		free(full_cmd_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

// X_OKやってからF_OKやるらしい(shellの挙動として)
// その辺を修正しつつpipexからコードを持ってきたり
char	*search_path(const char *filename, t_map *envmap)
{
	char	*path;

	path = search_path_mode(filename, X_OK, envmap);
	if (path)
		return (path);
	path = search_path_mode(filename, F_OK, envmap);
	return (path);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:00:20 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 14:35:50 by yurishik         ###   ########.fr       */
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

char	*search_path(const char *filename, t_map *envmap)
{
	char	*path;

	path = search_path_mode(filename, X_OK, envmap);
	if (path)
		return (path);
	path = search_path_mode(filename, F_OK, envmap);
	return (path);
}

int	set_path_cd(char *path, char *pwd, char **argv, t_map *envmap)
{
	char	*home;
	char	*oldpwd_str;

	if (pwd == NULL)
		oldpwd_str = xstrdup("OLDPWD");
	else
		oldpwd_str = join_str_separator("OLDPWD", pwd, '=');
	map_set(envmap, oldpwd_str, FALSE);
	free(oldpwd_str);
	if (argv[1] == NULL)
	{
		home = xgetenv(envmap, "HOME");
		if (home == NULL)
		{
			perror_wrapper("cd", NULL, "HOME not set");
			return (FAILED);
		}
		ft_strlcpy(path, home, PATH_MAX);
	}
	else
		ft_strlcpy(path, argv[1], PATH_MAX);
	return (SUCCESS);
}

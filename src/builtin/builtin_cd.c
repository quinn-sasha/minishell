/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:55:49 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/19 19:34:43 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_path(char **compressed_array, const char *part, size_t *j)
{
	if (ft_strcmp(part, ".") == 0)
		return ;
	else if (ft_strcmp(part, "..") == 0)
	{
		if ((*j) > 0)
		{
			free(compressed_array[(*j) - 1]);
			compressed_array[(*j) - 1] = NULL;
			(*j)--;
		}
	}
	else
	{
		compressed_array[(*j)] = xstrdup(part);
		(*j)++;
	}
}

char	**compress_path_array(char **path_array)
{
	char	**compressed_array;
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	j = 0;
	compressed_array = (char **)xcalloc(count_array(path_array) + 1,
			sizeof(char *));
	line = path_array[i];
	while (line != NULL)
	{
		process_path(compressed_array, line, &j);
		i++;
		line = path_array[i];
	}
	free_array(path_array);
	return (compressed_array);
}

char	*create_final_path(char **path_array)
{
	char	**compressed_array;
	char	*result;
	char	*tmp;
	size_t	i;

	i = 0;
	compressed_array = compress_path_array(path_array);
	if (compressed_array == NULL || compressed_array[0] == NULL)
		return (xstrdup("/"));
	result = xstrdup("");
	while (compressed_array[i] != NULL)
	{
		tmp = join_str_separator(result, compressed_array[i], '/');
		free(result);
		result = tmp;
		i++;
	}
	return (result);
}

char	*resolve_pwd(char *pwd, char *path)
{
	char	**path_array;
	char	*new_path;
	char	*new_pwd;

	if (pwd == NULL || *path == '/')
		new_path = xstrdup(path);
	else
		new_path = join_str_separator(pwd, path, '/');
	path_array = ft_split(new_path, '/');
	free(new_path);
	if (path_array == NULL)
	{
		new_pwd = xstrdup("/");
		return (new_pwd);
	}
	new_pwd = create_final_path(path_array);
	return (new_pwd);
}

int	builtin_cd(char **argv, t_map *envmap)
{
	char	*pwd;
	char	path[PATH_MAX];
	char	*new_pwd;

	pwd = xgetenv(envmap, "PWD");
	if (set_path_cd(path, pwd, argv, envmap) == FAILED)
		return (1);
	if (chdir(path) < 0)
	{
		perror_wrapper("cd", "no such file or directory", path);
		return (1);
	}
	new_pwd = resolve_pwd(pwd, path);
	map_set(envmap, join_str_separator("PWD", new_pwd, '='), FALSE);
	free(new_pwd);
	return (SUCCESS);
}

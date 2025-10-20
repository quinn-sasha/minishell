/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:36:46 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 08:36:47 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
command_nameに対応する実行可能ファイルへの、絶対パスを取得する。
もしファイルが存在しなければ、NULLを返す。
*/
char	*find_path(char *command_name)
{
	char	**paths;
	int		i;
	char	*dir_path;
	char	*path;

	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths[i])
	{
		dir_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(dir_path, command_name);
		free(dir_path);
		if (access(path, F_OK) == FAILED)
		{
			free(path);
			i++;
			continue ;
		}
		free_words(paths);
		return (path);
	}
	free_words(paths);
	return (NULL);
}

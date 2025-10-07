/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:00:20 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/07 17:50:53 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief PATH環境変数を走査し、指定されたアクセスモードで実行ファイルへのパスを検索する。
 *
 * @param filename 検索対象のコマンド名
 * @param mode     アクセスチェックモード (X_OK, F_OKなど)
 * @param envmap   環境変数マップのポインタ
 * @return 実行ファイルへのフルパス（ヒープ確保）、またはNULL (見つからなかった場合)。
 * @details PATH環境変数を':'で分割し、各ディレクトリでファイルを探しaccess(2)で検証する。
 */
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

/**
 * @brief コマンドの実行可能パスを検索する。
 *
 * @param filename 検索対象のコマンド名
 * @param envmap   環境変数マップのポインタ
 * @return 実行ファイルのフルパス（ヒープ確保）。見つからない場合はNULL。
 * @details 最初にX_OK（実行可能）で検索し、次にF_OK（存在のみ）で再検索する二段階検索を行う。
 */
char	*search_path(const char *filename, t_map *envmap)
{
	char	*path;

	path = search_path_mode(filename, X_OK, envmap);
	if (path)
		return (path);
	path = search_path_mode(filename, F_OK, envmap);
	return (path);
}

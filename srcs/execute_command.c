/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 20:32:48 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/16 15:56:51 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_full_path(const char *dir, const char *cmd, char **full_path)
{
	size_t	dir_len;
	size_t	cmd_len;
	size_t	i;
	size_t	j;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	*full_path = (char *)malloc(dir_len + 1 + cmd_len + 1);
	if (!(*full_path))
		return (FAILURE);
	i = 0;
	while (i < dir_len)
	{
		(*full_path)[i] = dir[i];
		i++;
	}
	(*full_path)[i++] = '/';
	j = 0;
	while (j < cmd_len)
	{
		(*full_path)[i++] = cmd[j];
		j++;
	}
	(*full_path)[i] = '\0';
	return (SUCCESS);
}

/**
 * @brief dir + "/" + cmd の文字列を malloc して作る
 * 
 * @param dir ディレクトリ部分
 * @param cmd コマンド名
 * @param full_path 出力用ポインタ malloc
 * @return 0: 成功, 1: メモリ確保失敗
 */
int	make_full_path(const char *dir, const char *cmd, char **full_path)
{
	if (!dir || !cmd || !full_path)
		return (FAILURE);
	if (set_full_path(dir, cmd, full_path) != 0)
		return (FAILURE);
	return (SUCCESS);
}

int	check_and_exec(char *dir, char **tokens, char **envp)
{
	char	*full_path;

	full_path = NULL;
	if (make_full_path(dir, tokens[0], &full_path) != 0)
	{
		free(dir);
		free(full_path);
		return (FAILURE);
	}
	if (access(full_path, F_OK | X_OK) == 0)
	{
		execve(full_path, tokens, envp);
	}
	free(full_path);
	return (SUCCESS);
}

int	try_exec_paths(char **tokens, char **envp, char *path_env)
{
	int		i;
	int		start;
	char	*dir;

	if (!tokens || !tokens[0] || !path_env)
		return (FAILURE);
	i = 0;
	start = 0;
	while (path_env[i])
	{
		if (path_env[i] == ':')
		{
			if (ft_strndup(path_env + start, i - start, &dir) != 0)
				return (FAILURE);
			if (check_and_exec(dir, tokens, envp) == FAILURE)
				return (FAILURE);
			free(dir);
			start = i + 1;
		}
		i++;
	}
	return (FAILURE);
}

void	execute_command(char **tokens, char **envp)
{
	char	*path_env;
	pid_t	pid;

	if (!tokens || !tokens[0])
		return ;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
	{
		path_env = getenv("PATH");
		if (!path_env || try_exec_paths(tokens, envp, path_env))
		{
			print_command_not_found(tokens[0]);
			exit(127);
		}
	}
}

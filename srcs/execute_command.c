/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 20:32:48 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/08 09:41:11 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief command not foundのエラーを出す
 *
 * @author yurishik
 * @param cmd 出力するためのコマンド名
 * TODO: ft_putstr_fdで書き換えたい気持ちがある
 */
void	print_command_not_found(const char *cmd)
{
	write(STD_ERR, "minishell: ", 11);
	write(STD_ERR, cmd, strlen(cmd));
	write(STD_ERR, ": command not found\n", 20);
}

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

int	try_exec_paths(char **tokens, char **envp, char *path_env)
{
	char	*dir;
	char	*full_path;
	int		i;
	int		start;

	dir = NULL;
	full_path = NULL;
	i = 0;
	start = 0;
	if (!tokens || !tokens[0] || !path_env)
		return (FAILURE);
	while (path_env[i])
	{
		if (path_env[i] == ':')
		{
			if (ft_strndup(path_env + start, i - start, &dir) != 0
				|| make_full_path(dir, tokens[0], &full_path) != 0)
			{
				free(dir);
				free(full_path);
				return (FAILURE);
			}
			free(dir);
			if (access(full_path, F_OK | X_OK) == 0)
				execve(full_path, tokens, envp);
			free(full_path);
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

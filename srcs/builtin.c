/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:37:04 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/02 14:48:19 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 入力文字列がビルトインコマンドか判定して実行する
 *
 * @param input ユーザー入力文字列
 * @return ビルトインを実行したら1、実行しなかったら0
 */
int	check_builtin(const char *input)
{
	if (is_builtin(input, "pwd"))
	{
		builtin_pwd();
		return (1);
	}
	if (is_builtin(input, "exit"))
	{
		builtin_exit();
		return (1);
	}
	return (0);
}

/**
 * @brief 入力文字列が指定したビルトインコマンドかを判定する、前後のスペースがあっても判定する
 *
 * @author yurishik
 * @param input 入力文字列
 * @param cmd 比較するコマンド名
 * @return 一致すれば1、そうでなければ0
 */
int	is_builtin(const char *input, const char *cmd)
{
	int	i;
	int	j;
	int	len;

	if (!input)
		return (FLG_FALSE);
	i = 0;
	len = ft_strlen(cmd);
	while (input[i] != '\0' && is_separator(input[i]))
		i++;
	j = 0;
	while (j < len)
	{
		if (input[i + j] != cmd[j])
			return (FLG_FALSE);
		j++;
	}
	i += len;
	while (input[i] != '\0' && is_separator(input[i]))
		i++;
	if (input[i] == '\0')
		return (FLG_TRUE);
	return (FLG_FALSE);
}

/**
 * @brief ビルトイン関数のpwd
 *
 * @author yurishik
 * @return 正常なら0、エラーなら1(ディレクトリが存在しない場合などに発生)
 */
int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
		return (SUCCESS);
	}
	else
	{
		perror("pwd");
		return (FAILURE);
	}
}

/**
 * @brief ビルトイン関数のexit
 *
 * @author yurishik
 * @return exitするので到達はしないはず
 */
int	builtin_exit(void)
{
	printf("exit\n");
	exit(0);
	return (0);
}

int	builtin_unset(t_env **head, const char *name)
{
	return unset_env(head, name);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:37:04 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/02 16:58:25 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 入力文字列がビルトインコマンドか判定して実行する
 *
 * @param argv 
 * @return ビルトインを実行したらSUCCESS、実行しなかったらFAILURE
 */
int	check_builtin(t_env **env, char *input)
{
	char	**tokens;
	int		status;

	status = FAILURE;
	if (split_by_separator(input, &tokens) != 0)
	{
		printf("error: cannot split by separator\n");
		return (FAILURE);
	}
	/*
	if (is_builtin(tokens[0], "echo"))
		status = builtin_echo(tokens); // echo with option -n
	if (is_builtin(tokens[0], "cd"))
		status = builtin_cd(tokens); // cd with only a relative or absolute path
	*/
	if (is_builtin(tokens[0], "pwd"))
		status = builtin_pwd(); // pwd with no options
	else if (is_builtin(tokens[0], "export"))
		status = builtin_export(env, tokens[1]); // export with no options
	else if (is_builtin(tokens[0], "unset"))
		status = builtin_unset(env, tokens[1]); // unset with no options
	else if (is_builtin(tokens[0], "env"))
	{
		builtin_env(*env); // env with no options or arguments
		return (SUCCESS);
	}
	else if (is_builtin(tokens[0], "exit"))
		status = builtin_exit(tokens); // exit with no options
	return (status);
}

/**
 * @brief 入力文字列が指定したビルトインコマンドかを判定する、前後のスペースがあっても判定する
 *
 * @author yurishik
 * @param input 入力文字列
 * @param cmd 比較するコマンド名
 * @return 一致すればFLG_TRUE、そうでなければFLG_FALSE
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

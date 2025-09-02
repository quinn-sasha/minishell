/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:00:50 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/02 20:31:14 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief パイプの記号であるかどうかを判定する
 *
 * @author yurishik
 * @param c 判定したい文字
 * @return パイプの記号であれば1、そうでなければ0
 */
int	is_pipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

/**
 * @brief パイプの記号が何個あるかをカウントする
 *
 * @author yurishik
 * @param input 入力文字列
 * @return パイプの記号の個数
 */
int	count_pipes(const char *input)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (input && input[i])
	{
		if (input[i] == '|')
			count++;
		i++;
	}
	return (count);
}

/**
 * @brief 入力文字列をパイプごとに分割して配列に格納する
 *
 * @author yurishik
 * @param input 入力文字列
 * @param res 分割結果を格納する配列
 * @return 正常終了なら0、エラーなら1
 */
int	split_loop(const char *input, char **res)
{
	int	start;
	int	i;
	int	idx;

	start = 0;
	i = 0;
	idx = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (ft_strndup(input + start, i - start, &res[idx]) != 0)
				return (1);
			idx++;
			start = i + 1;
		}
		i++;
	}
	if (ft_strndup(input + start, i - start, &res[idx]) != 0)
		return (1);
	idx++;
	res[idx] = NULL;
	return (0);
}

/**
 * @brief パイプの記号で分割して配列に入れる
 *
 * @author yurishik
 * @param input 分割したい文字列
 * @param commands 分割結果を入れる配列のポインタ malloc
 * @param num_cmd 分割したコマンド数
 * @return 正しく実行されたら0、エラーが起きたら1
 */
int	split_by_pipe(const char *input, char ***commands, int *num_cmd)
{
	char	**result;

	if (!input || !commands)
		return (1);
	*num_cmd = count_pipes(input) + 1;
	result = (char **)malloc(sizeof(char *) * (*num_cmd + 1));
	if (!result)
		return (1);
	if (split_loop(input, result) != 0)
	{
		free_str_array(result);
		return (1);
	}
	*commands = result;
	return (0);
}

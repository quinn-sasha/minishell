/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_separator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:00:50 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/03 11:50:49 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief separator(現在はスペースとタブのみ)であるかどうかを判定する, IFS未対応
 *
 * @author yurishik
 * @param c 判定したい文字
 * @return separatorに当てはまるなら1、そうでなければ0
 */
int	is_separator(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

/**
 * @brief トークンが何個あるかをカウントする
 *
 * @author yurishik
 * @param input 入力文字列
 * @return トークン数
 */
int	count_tokens(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		while (is_separator(input[i]))
			i++;
		if (input[i])
			count++;
		while (input[i] && !is_separator(input[i]))
			i++;
	}
	return (count);
}

/**
 * @brief 入力文字列をseparatorごとに分割して配列に格納する
 *
 * @author yurishik
 * @param input 入力文字列
 * @param res 分割結果を格納する配列
 * @return 正常終了なら0、エラーなら1
 */
int	split_separator_loop(const char *input, char **res)
{
	int	start;
	int	i;
	int	r_idx;

	start = 0;
	i = 0;
	r_idx = 0;
	while (input[i])
	{
		while (input[i] && !is_separator(input[i]))
			i++;
		if (i > start)
		{
			if (ft_strndup(input + start, i - start, &res[r_idx]) != 0)
				return (1);
			r_idx++;
		}
		while (is_separator(input[i]))
			i++;
		start = i;
	}
	res[r_idx] = NULL;
	return (0);
}

/**
 * @brief separatorで分割して配列に入れる
 *
 * @author yurishik
 * @param input 分割したい文字列
 * @param commands 分割結果を入れる配列のポインタ malloc
 * @param num_cmd 分割したコマンド数
 * @return 正しく実行されたら0、エラーが起きたら1
 */
int	split_by_separator(const char *input, char ***tokens)
{
	char	**result;
	int		num_tokens;

	if (!input || !tokens)
		return (1);
	num_tokens = count_tokens((char *)input);
	result = (char **)malloc(sizeof(char *) * (num_tokens + 1));
	if (!result)
		return (1);
	if (split_separator_loop(input, result) != 0)
	{
		free_str_array(result);
		return (1);
	}
	*tokens = result;
	return (0);
}

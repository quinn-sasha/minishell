/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:00:50 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/16 16:07:43 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief パイプの記号であるかどうかを判定する
 *
 * @author yurishik
 * @param c 判定したい文字
 * @return パイプの記号であればFLG_TRUE、そうでなければFLG_FALSE
 */
int	is_pipe(char c)
{
	if (c == '|')
		return (FLG_TRUE);
	return (FLG_FALSE);
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
		if (is_pipe(input[i]))
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
 * @return 正常終了ならSUCCESS、エラーならFAILURE
 */
int	split_pipe_loop(const char *input, char **res)
{
	int	start;
	int	i;
	int	r_idx;

	start = 0;
	i = 0;
	r_idx = 0;
	while (input[i])
	{
		if (!is_pipe(input[i]))
		{
			i++;
			continue ;
		}
		if (ft_strndup(input + start, i - start, &res[r_idx]) != 0)
			return (FAILURE);
		r_idx++;
		start = i + 1;
		i++;
	}
	if (ft_strndup(input + start, i - start, &res[r_idx]) != 0)
		return (FAILURE);
	r_idx++;
	res[r_idx] = NULL;
	return (SUCCESS);
}

/**
 * @brief パイプの記号で分割して配列に入れる
 *
 * @author yurishik
 * @param input 分割したい文字列
 * @param commands 分割結果を入れる配列のポインタ malloc
 * @param num_cmd 分割したコマンド数
 * @return 正しく実行されたらSUCCESS、エラーが起きたらFAILURE
 */
int	split_by_pipe(const char *input, char ***commands, int *num_cmd)
{
	char	**result;

	if (!input || !commands)
		return (FAILURE);
	*num_cmd = count_pipes(input) + 1;
	result = (char **)malloc(sizeof(char *) * (*num_cmd + 1));
	if (!result)
		return (FAILURE);
	if (split_pipe_loop(input, result) != 0)
	{
		free_str_array(result);
		return (FAILURE);
	}
	*commands = result;
	return (SUCCESS);
}

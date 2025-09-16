/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:02:24 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/16 18:50:10 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 環境変数名の1文字目として適切な英字か_であることを確認する
 *
 * @author yurishik
 * @param c チェックしたい文字
 * @return OKならFLG_TRUE, NGならFLG_FALSE
 */
int	is_env_key_first_char(char c)
{
	return (isalpha(c) || c == '_');
}

/**
 * @brief 環境変数名の2文字目以降として適切な英字か数字か_であることを確認する
 *
 * @author yurishik
 * @param c チェックしたい文字
 * @return OKならFLG_TRUE, NGならFLG_FALSE
 */
int	is_env_key_char(char c)
{
	return (isalnum(c) || c == '_');
}

/**
 * @brief 環境変数名として問題ないかのvalid (TODO: 使える文字種かどうかを確認する部分を追記)
 *        環境変数追加時に確認すること？
 * @author yurishik
 * @param name チェックしたい文字列
 * @return 環境変数名としてOKならFLG_TRUE, NGならFLG_FALSE
 */
int	is_env_key_name(const char *name)
{
	int	len;
	int	i;

	len = ft_strlen(name);
	if (len <= 0)
		return (FLG_FALSE);
	i = 0;
	while (i < len)
	{
		if (i == 0 && !is_env_key_first_char(name[i]))
			return (FLG_FALSE);
		if (i != 0 && !is_env_key_char(name[i]))
			return (FLG_FALSE);
		i++;
	}
	return (FLG_TRUE);
}

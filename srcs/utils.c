/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:40:33 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/08 08:54:43 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 文字列の配列を free する
 *
 * @param arr freeしたい配列
 */
void	free_str_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/**
 * @brief 文字列比較
 *
 * @author yurishik
 * @param s1
 * @param s2
 * @return 一致していたら0、異なれば0以外
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/**
 * @brief 文字列をn文字比較
 *
 * @author yurishik
 * @param s1
 * @param s2
 * @return 一致していたら0、異なれば0以外
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

/**
 * @brief 文字列の長さを返す。abcdeなら5が返ってくる
 *
 * @author yurishik
 * @param s 長さを調べたい文字列
 * @return 文字列の長さ
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/**
 * @brief 文字列sの先頭n文字をコピーして新しい文字列に格納
 *
 * @param s コピー元の文字列
 * @param n コピーする文字数
 * @param dest コピー先のポインタ malloc
 * @return 0: 成功, 1: エラー
 */
int	ft_strndup(const char *s, size_t n, char **dest)
{
	size_t	i;
	size_t	j;
	char	*result;

	if (!s || !dest)
		return (1);
	i = 0;
	while (s[i] && i < n)
		i++;
	result = (char *)malloc(i + 1);
	if (!result)
		return (1);
	j = 0;
	while (j < i)
	{
		result[j] = s[j];
		j++;
	}
	result[i] = '\0';
	*dest = result;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:57:10 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/16 18:50:35 by yurishik         ###   ########.fr       */
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

int	ft_isalpha(int c)
{
	if ('A' <= c && c <= 'Z')
		return (FLG_TRUE);
	if ('a' <= c && c <= 'z')
		return (FLG_TRUE);
	return (FLG_FALSE);
}

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (FLG_TRUE);
	return (FLG_FALSE);
}

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

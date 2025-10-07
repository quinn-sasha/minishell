/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:59:11 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/07 18:54:13 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief リダイレクトを実行し、標準FDをファイルに付け替え、元のFDを保存する。
 *
 * @param redirect 処理対象のリダイレクトノードのリスト
 * @details ターゲットFD(from.fd)の接続をstash_fdに保存後、file_fdの接続で上書き(dup2)する。
 * 複製に使用したfile_fdはFDリークを防ぐため即座に閉じる。
 */
void	do_redirect(t_redirect *redirect)
{
	if (redirect == NULL)
		return ;
	redirect->stash_fd = xdup(redirect->from.fd);
	xdup2(redirect->file_fd, redirect->from.fd);
	close(redirect->file_fd);
	do_redirect(redirect->next);
}

/**
 * @brief リダイレクト処理を解除し、FDの復元を行う。
 *
 * @param redirect 復元対象のリダイレクトノードのリスト
 * @details リストを末尾から再帰的に処理し、stash_fdを使って元の標準FD接続を復元する。
 * 復元後、保存用FD(stash_fd)はクローズされる。
 */
void	reset_redirect(t_redirect *redirect)
{
	if (redirect == NULL)
		return ;
	reset_redirect(redirect->next);
	if (redirect->stash_fd > 0)
	{
		xdup2(redirect->stash_fd, redirect->from.fd);
		close(redirect->stash_fd);
	}
}

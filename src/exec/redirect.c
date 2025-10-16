/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:59:11 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/16 14:16:48by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int open_fd(t_redirect *redirect, t_map *envmap) {
	char *pathname = redirect->to.filename;
	if (redirect->redirect_kind == r_reading_until) {
		return read_heredoc(pathname, envmap);
	}
	return open(pathname, redirect->open_flags, 0644);
}

int	open_redirect_file(t_simple_command *command, t_map *envmap)
{
	int			flags;
	t_redirect	*current;

	current = command->redirect;
	while (current != NULL)
	{
		current->file_fd = open_fd(current, envmap);
		if (current->file_fd < 0)
			return (FAILED);
		current = current->next;
	}
	return (SUCCESS);
}

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

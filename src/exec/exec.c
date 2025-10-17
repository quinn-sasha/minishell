/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:52:45 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/16 15:37:11 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief t_tokenのリンクリストをNULL終端のchar**配列に変換する。
 *
 * @param token コマンド引数のリストの先頭
 * @return NULL終端のchar**配列（execve用）
 */
char	**tokens_to_argv(t_token *token)
{
	char	**argv;
	t_token	*current;
	size_t	i;
	size_t	j;

	i = count_token(token);
	argv = xcalloc(i + 1, sizeof(char *));
	j = 0;
	current = token;
	while (j < i && current != NULL && current->token_kind != TOKEN_EOF)
	{
		argv[j] = xstrdup(current->word);
		j++;
		current = current->next;
	}
	return (argv);
}

/**
 * @brief 外部コマンドの実行前にパスの有効性とアクセス権を検証する。
 *
 * @param path コマンドのフルパスまたは相対パス
 * @param cmd  ユーザーが入力した元のコマンド名 (エラーメッセージ用)
 * @details ファイルの存在(F_OK)と実行権限(X_OK)を確認し、失敗時はexit(126/127)で終了する。
 */
void	validate_access(char *path, char *cmd)
{
	struct stat	st;

	if (path == NULL)
		error_and_exit(cmd, COMMAND_NOT_FOUND_ERROR, COMMAND_NOT_FOUND_STATUS);
	if (access(path, F_OK) < 0)
	{
		if (errno == ENOENT)
			error_and_exit(cmd, "No such file or directory",
				COMMAND_NOT_FOUND_STATUS);
		else
			error_and_exit(cmd, COMMAND_NOT_FOUND_ERROR,
				COMMAND_NOT_FOUND_STATUS);
	}
	if (stat(path, &st) < 0)
		fatal_error("fstat");
	if (S_ISDIR(st.st_mode))
		error_and_exit(cmd, "is a directory", PERMISSION_DENIED_STATUS);
	if (access(path, X_OK) < 0)
		error_and_exit(cmd, PERMISSION_DENIED_ERROR, PERMISSION_DENIED_STATUS);
}

/**
 * @brief 子プロセス内で外部コマンドを実行し、成功時はプロセスを上書きする。
 *
 * @param command 実行対象のコマンド構造体
 * @param envmap  環境変数マップのポインタ
 * @details execveが成功すると戻らず、失敗時はリダイレクトを復元しリソースを解放する。
 */
void	exec_nonbuiltin(t_simple_command *command, t_map *envmap)
{
	char	**argv;
	char	*path;
	char	**environ;

	if (open_redirect_file(command, envmap) == FAILED)
		exit(1);
	do_redirect(command->redirect);
	argv = tokens_to_argv(command->arguments);
	path = argv[0];
	if (ft_strchr(path, '/') == -1)
		path = search_path(path, envmap);
	validate_access(path, argv[0]);
	environ = get_envmap(envmap);
	execve(path, argv, environ);
	free_array(argv);
	reset_redirect(command->redirect);
	free_array(environ);
	fatal_error("execve");
}

/**
 * @brief コマンド実行の制御を行い、終了ステータスを返す。
 *
 * @param command 実行対象のコマンド
 * @param envmap  環境変数マップのポインタ
 * @return コマンドの終了ステータス。
 * @details コマンドが単体builtinであれば親で実行し、それ以外はパイプラインとして子プロセスを起動する。
 */
int	exec(t_simple_command *command, t_map *envmap)
{
	pid_t	last_pid;
	int		status;

	if (command->next == NULL && is_builtin(command))
		status = exec_builtin(command, envmap);
	else
	{
		last_pid = exec_pipe(command, envmap);
		status = wait_pipe(last_pid);
	}
	envmap->last_status = status;
	return (status);
}

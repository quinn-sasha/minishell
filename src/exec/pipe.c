/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:23:29 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/16 15:41:40 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief パイプラインの次のコマンドとのパイプを確立する。
 *
 * @param command 現在処理中のコマンドノード
 * @details 次のノードが存在する場合、outpipeを生成し、そのFDを次のノードのinpipeにコピーする。
 */
void	prepare_pipe(t_simple_command *command)
{
	if (command->next == NULL)
		return ;
	xpipe(command->outpipe);
	command->next->inpipe[0] = command->outpipe[0];
	command->next->inpipe[1] = command->outpipe[1];
}

/**
 * @brief 子プロセス内で入出力をパイプに接続し、不要なFDをクローズする。
 *
 * @param command 現在処理中のコマンドノード
 * @details inpipeをSTDIN(0)に、outpipeをSTDOUT(1)にdup2(2)で付け替え、元のFDを解放する。
 */
void	prepare_pipe_child(t_simple_command *command)
{
	xclose(command->outpipe[0]);
	xdup2(command->inpipe[0], STDIN_FILENO);
	if (command->inpipe[0] != STDIN_FILENO)
		xclose(command->inpipe[0]);
	xdup2(command->outpipe[1], STDOUT_FILENO);
	if (command->outpipe[1] != STDOUT_FILENO)
		xclose(command->outpipe[1]);
}

/**
 * @brief 親プロセス内で不要になったパイプのFDをクローズする。
 *
 * @param command 現在処理中のコマンドノード
 * @details 親が使用しないinpipeの読み込み側FDと、次のコマンドへ渡すためのoutpipeの書き込み側FDを閉じる。
 */
void	prepare_pipe_parent(t_simple_command *command)
{
	if (command->inpipe[0] != STDIN_FILENO)
		xclose(command->inpipe[0]);
	if (command->next)
		xclose(command->outpipe[1]);
}

/**
 * @brief パイプラインの最後のプロセスが終了するのを待ち、終了ステータスを回収する。
 *
 * @param last_pid パイプラインの最後のコマンドの子プロセスID
 * @return 回収された終了ステータス (0-255)。
 * @details wait(2)を繰り返し呼び出し、SIGINTなどによる強制終了も128+SIGNUMとして処理する。
 */
int	wait_pipe(pid_t last_pid)
{
	int		last_status;
	int		wait_status;
	pid_t	wait_pid;

	while (1)
	{
		wait_pid = wait(&wait_status);
		if (wait_pid == last_pid)
		{
			if (WIFSIGNALED(wait_status))
				last_status = 128 + WTERMSIG(wait_status);
			else
				last_status = WEXITSTATUS(wait_status);
		}
		else if (wait_pid < 0)
		{
			if (errno == ECHILD)
				break ;
			if (errno == EINTR)
				continue ;
			else
				fatal_error("wait");
		}
	}
	return (last_status);
}

/**
 * @brief パイプラインを構成するコマンドを再帰的にforkし、実行する。
 *
 * @param command 現在処理中のコマンドノード
 * @param envmap  環境変数マップ
 * @return パイプラインで最後に実行されたプロセスID (PID)。
 * @details prepare_pipeで接続を確立後、子プロセスでコマンドを実行し、親プロセスで次のコマンドへ再帰する。
 */
pid_t	exec_pipe(t_simple_command *command, t_map *envmap)
{
	pid_t	pid;

	if (open_redirect_file(command, envmap) == FAILED)
		fatal_error ("cannot open file");
	if (command == NULL || command->arguments == NULL)
		fatal_error ("no command");
	prepare_pipe(command);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	if (pid == 0)
	{
		reset_signal(SIGQUIT);
		reset_signal(SIGINT);
		prepare_pipe_child(command);
		if (is_builtin(command))
			exec_builtin(command, envmap);
		else
			exec_nonbuiltin(command, envmap);
	}
	prepare_pipe_parent(command);
	if (command->next)
		return (exec_pipe(command->next, envmap));
	return (pid);
}

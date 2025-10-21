/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:23:29 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/21 17:15:02 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_pipe(t_simple_command *command)
{
	if (command->next == NULL)
		return ;
	xpipe(command->outpipe);
	command->next->inpipe[0] = command->outpipe[0];
	command->next->inpipe[1] = command->outpipe[1];
}

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

void	prepare_pipe_parent(t_simple_command *command)
{
	if (command->inpipe[0] != STDIN_FILENO)
		xclose(command->inpipe[0]);
	if (command->next)
		xclose(command->outpipe[1]);
}

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

pid_t	exec_pipe(t_simple_command *command, t_map *envmap)
{
	pid_t	pid;

	if (command == NULL || command->arguments == NULL)
		assert_error("no command");
	prepare_pipe(command);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	if (pid == 0)
	{
		reset_signal(SIGQUIT);
		reset_signal(SIGINT);
		prepare_pipe_child(command);
		if (is_command_args_empty(command))
			execute_empty_command(command);
		if (is_builtin(command))
			exit(exec_builtin(command, envmap));
		else
			exec_nonbuiltin(command, envmap);
	}
	prepare_pipe_parent(command);
	if (command->next)
		return (exec_pipe(command->next, envmap));
	return (pid);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:52:45 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/21 16:34:03 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command_args_empty(t_simple_command *command)
{
	t_token	*args;

	if (command == NULL)
		return (TRUE);
	args = command->arguments;
	// ここでargsの中身を見る関数を作って実行したい
	if (args == NULL)
		return (TRUE);
	if (args->token_kind == TOKEN_EOF || args->word == NULL)
		return (TRUE);
	return (FALSE);
}

char	**tokens_to_argv(t_token *token)
{
	char	**argv;
	t_token	*current;
	size_t	i;
	size_t	j;

	i = count_token(token);
	if (i == 0)
		return (NULL);
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

void	exec_nonbuiltin(t_simple_command *command, t_map *envmap)
{
	char	**argv;
	char	*path;
	char	**environ;

	if (open_redirect_file(command->redirect) == FAILED)
		exit(1);
	do_redirect(command->redirect);
	argv = tokens_to_argv(command->arguments);
	path = argv[0];
	if (ft_strcmp(path, "") == 0 || ft_strcmp(path, "..") == 0)
		error_and_exit("''", COMMAND_NOT_FOUND_ERROR, COMMAND_NOT_FOUND_STATUS);
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

int	exec(t_simple_command *command, t_map *envmap)
{
	pid_t	last_pid;
	int		status;

	if (gather_heredoc(command, envmap) == FAILED)
		return (EXIT_FAILURE);
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

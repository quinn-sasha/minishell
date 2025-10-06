/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:52:45 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/06 20:18:06 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_str_separator(const char *s1, const char *s2, char sep)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)xcalloc(len1 + len2 + 2, sizeof(char));
	ft_memcpy(result, s1, len1);
	result[len1] = sep;
	ft_memcpy(result + len1 + 1, s2, len2);
	return (result);
}

size_t	count_map_item(t_map *envmap)
{
	t_item	*item;
	size_t	count;

	if (envmap == NULL)
		return (0);
	count = 0;
	item = envmap->head.next;
	while (item != NULL)
	{
		count++;
		item = item->next;
	}
	return (count);
}

char	**get_envmap(t_map *envmap)
{
	char	**env_array;
	t_item	*item;
	size_t	count;
	size_t	i;

	if (envmap == NULL)
		return (xcalloc(1, sizeof(char *)));
	count = count_map_item(envmap);
	env_array = (char **)xcalloc(count + 1, sizeof(char *));
	item = envmap->head.next;
	i = 0;
	while (item != NULL)
	{
		env_array[i] = join_str_separator(item->name, item->value, '=');
		item = item->next;
		i++;
	}
	return (env_array);
}

void	error_and_exit(const char *cmd, const char *message, int status)
{
	prefix_error();
	ft_dprintf(STDERR_FILENO, "%s: ", cmd);
	if (errno != 0)
		ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno));
	else
		ft_dprintf(STDERR_FILENO, "%s\n", message);
	exit(status);
}

void	free_array(char	**array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*search_path_mode(const char *filename, int mode, t_map *envmap)
{
	char	*envpath;
	char	**paths;
	char	*full_cmd_path;
	int		i;

	envpath = xgetenv(envmap, "PATH");
	if (!envpath)
		return (NULL);
	paths = ft_split(envpath, ':');
	if (!paths)
		fatal_error("malloc");
	i = 0;
	while (paths[i])
	{
		full_cmd_path = join_str_separator(paths[i], filename, '/');
		if (access(full_cmd_path, mode) == SUCCESS)
		{
			free_array(paths);
			return (full_cmd_path);
		}
		free(full_cmd_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

// X_OKやってからF_OKやるらしい(shellの挙動として)
// その辺を修正しつつpipexからコードを持ってきたり
char	*search_path(const char *filename, t_map *envmap)
{
	char	*path;

	path = search_path_mode(filename, X_OK, envmap);
	if (path)
		return (path);
	path = search_path_mode(filename, F_OK, envmap);
	return (path);
}

size_t	count_token(t_token *token)
{
	size_t	i;
	t_token	*current;

	i = 0;
	current = token;
	while (current->token_kind != TOKEN_EOF)
	{
		i++;
		current = current->next;
	}
	return (i);
}

// t_tokenのargumentsをchar**にする
char	**tokens_to_argv(t_token *token)
{
	char	**argv;
	t_token	*current;
	size_t	i;

	i = count_token(token);
	argv = xcalloc(i + 1, sizeof(char *));
	i = 0;
	current = token;
	while (current->token_kind != TOKEN_EOF)
	{
		argv[i] = xstrdup(current->word);
		i++;
		current = current->next;
	}
	return (argv);
}

void	do_redirect(t_redirect *redirect)
{
	if (redirect == NULL)
		return ;
	redirect->stash_fd = xdup(redirect->from.fd);
	xdup2(redirect->file_fd, redirect->from.fd);
	close(redirect->file_fd);
	do_redirect(redirect->next);
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

// コマンド構造体を元にbuiltinではない関数を実行する
void	exec_nonbuiltin(t_simple_command *command, t_map *envmap)
{
	char	**argv;
	char	*path;
	char	**environ;

	argv = tokens_to_argv(command->arguments);
	path = argv[0];
	if (ft_strchr(path, '/') == -1)
		path = search_path(path, envmap);
	validate_access(path, argv[0]);
	environ = get_envmap(envmap);
	do_redirect(command->redirect);
	execve(path, argv, environ);
	free_array(argv);
	// reset_redirect //TODO
	free_array(environ);
	fatal_error("execve");
}

// return last_status
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

int	exec_builtin(void)
{
	return (0);
}

int	is_builtin(void)
{
	return (0); // TODO
}

// return last pid
pid_t	exec_pipe(t_simple_command *command, t_map *envmap)
{
	pid_t	pid;

	if (command == NULL || command->arguments == NULL)
		return (-1);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	if (pid == 0)
	{
		reset_signal(SIGQUIT);
		reset_signal(SIGINT);
		// prepare_pipe_child(command);
		if (is_builtin())
			exec_builtin();
		else
			exec_nonbuiltin(command, envmap);
	}
	// prepare_pipe_parent(command);
	if (command->next)
		return (exec_pipe(command->next, envmap));
	return (pid);
}

int	exec(t_simple_command *command, t_map *envmap)
{
	pid_t	last_pid;
	int		status;

	command->redirect->file_fd = open(command->redirect->to.filename,
			command->redirect->open_flags);
	if (command->next == NULL && is_builtin())
	{
		status = exec_builtin();
	}
	else
	{
		last_pid = exec_pipe(command, envmap);
		status = wait_pipe(last_pid);
	}
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:52:45 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/06 14:42:22 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	*path_join(const char *dir_path, const char *cmd)
{
	size_t	dir_len;
	size_t	cmd_len;
	char	*result;

	dir_len = ft_strlen(dir_path);
	cmd_len = ft_strlen(cmd);
	result = (char *)xcalloc(dir_len + cmd_len + 2, sizeof(char));
	ft_memcpy(result, dir_path, dir_len);
	result[dir_len] = '/';
	ft_memcpy(result + dir_len + 1, cmd, cmd_len);
	return (result);
}

char	*search_path_mode(const char *filename, int mode)
{
	char	*envpath;
	char	**paths;
	char	*full_cmd_path;
	int		i;

	envpath = xgetenv("PATH");
	if (!envpath)
		return (NULL);
	paths = ft_split(envpath, ':');
	if (!paths)
		fatal_error("malloc");
	i = 0;
	while (paths[i])
	{
		full_cmd_path = path_join(paths[i], filename);
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
char	*search_path(const char *filename)
{
	char	*path;

	path = search_path_mode(filename, X_OK);
	if (path)
		return (path);
	path = search_path_mode(filename, F_OK);
	return (path);
}

int	count_token(t_token *token)
{
	int		i;
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

/*
void	do_redirect(t_redirect *redirect)
{
	if (redirect == NULL)
		return ;
	if (is_redirect(redirect))
	{
		// stashfdに当たる部分が必要ということ？ちょい混乱中なので後回し
	}
	else
		assert_error("redirect");
	do_redirect(redirect->next);
}
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

// コマンド構造体を元にbuiltinではない関数を実行する
void	exec_nonbuiltin(t_simple_command *command)
{
	char	**argv;
	char	*path;

	argv = tokens_to_argv(command->arguments);
	path = argv[0];
	if (ft_strchr(path, '/') == -1)
		path = search_path(path);
	validate_access(path, argv[0]);
	// do_redirect(command->redirect);
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

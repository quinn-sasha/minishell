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
		if (access(full_cmd_path, mode) == 0)
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

// t_tokenのargumentsをchar**にする
char	**tokens_to_argv(t_token *token)
{
	char	**argv;
	t_token	*current;
	size_t	i;

	i = 0;
	current = token;
	while (current->token_kind != TOKEN_EOF)
	{
		i++;
		current = current->next;
	}
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

// コマンド構造体を元にbuiltinではない関数を実行する
void exec_nonbuiltin(t_simple_command *command)
{
	char	**argv;
	char	*path;
	argv = tokens_to_argv(command->arguments);
	path = argv[0];
	// TODO
}

// return last_status
int	wait_pipe(pid_t last_pid)
{
	int	last_status;
	int	wait_status;
	pid_t wait_pid;
	
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
		else if (wait_pid < 0) // error
		{
			if (errno == ECHILD)
				break;
			if (errno == EINTR)
				continue;
			else
				fatal_error("wait"); // TODO
		}
	}
	return (last_status);
}
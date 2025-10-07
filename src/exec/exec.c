/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:52:45 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/07 17:03:22 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_str_separator(const char *s1, const char *s2, char sep)
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
	reset_redirect(command->redirect);
	free_array(environ);
	fatal_error("execve");
}

int	exec(t_simple_command *command, t_map *envmap)
{
	pid_t	last_pid;
	int		status;

	if (command->redirect != NULL)
		command->redirect->file_fd = open(command->redirect->to.filename,
				command->redirect->open_flags);
	if (command->next == NULL && is_builtin())
	{
		status = exec_builtin(command, envmap);
	}
	else
	{
		last_pid = exec_pipe(command, envmap);
		status = wait_pipe(last_pid);
	}
	return (status);
}

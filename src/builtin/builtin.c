/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:49:45 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/21 16:36:10 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_builtin_command(char **argv, t_map *envmap)
{
	if (ft_strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argv, envmap));
	if (ft_strcmp(argv[0], "export") == 0)
		return (builtin_export(argv, envmap));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (builtin_unset(argv, envmap));
	if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env(envmap));
	if (ft_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(argv, envmap));
	if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argv));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd());
	return (1);
}

int	exec_builtin(t_simple_command *command, t_map *envmap)
{
	int		status;
	char	**argv;

	if (open_redirect_file(command->redirect) == FAILED)
		return (1);
	do_redirect(command->redirect);
	status = 0;
	argv = tokens_to_argv(command->arguments);
	status = exec_builtin_command(argv, envmap);
	free_array(argv);
	reset_redirect(command->redirect);
	return (status);
}

int	is_builtin(t_simple_command *command)
{
	char	**argv;

	argv = tokens_to_argv(command->arguments);
	if (argv == NULL || argv[0] == NULL)
		return (FALSE);
	if (ft_strcmp(argv[0], "exit") == 0
		|| ft_strcmp(argv[0], "export") == 0
		|| ft_strcmp(argv[0], "unset") == 0
		|| ft_strcmp(argv[0], "env") == 0
		|| ft_strcmp(argv[0], "cd") == 0
		|| ft_strcmp(argv[0], "echo") == 0
		|| ft_strcmp(argv[0], "pwd") == 0)
	{
		free_array(argv);
		return (TRUE);
	}
	free_array(argv);
	return (FALSE);
}

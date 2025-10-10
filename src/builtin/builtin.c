/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:49:45 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/09 19:38:27 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_simple_command *command, t_map *envmap)
{
	int		status;
	char	**argv;

	status = 0;
	argv = tokens_to_argv(command->arguments);
	if (ft_strcmp(argv[0], "export") == 0)
		status = builtin_export(argv, envmap);
	if (ft_strcmp(argv[0], "unset") == 0)
		status = builtin_unset(argv, envmap);
	if (ft_strcmp(argv[0], "env") == 0)
		status = builtin_env(envmap);
	if (ft_strcmp(argv[0], "echo") == 0)
		status = builtin_echo(argv);
	if (ft_strcmp(argv[0], "pwd") == 0)
		status = builtin_pwd();
	free_array(argv);
	return (status);
}

int	is_builtin(t_simple_command *command)
{
	char	**argv;

	argv = tokens_to_argv(command->arguments);
	if (argv[0] == NULL)
		return (FALSE);
	if (ft_strcmp(argv[0], "exit") == 0
		|| ft_strcmp(argv[0], "export") == 0
		|| ft_strcmp(argv[0], "unset") == 0
		|| ft_strcmp(argv[0], "env") == 0
		|| ft_strcmp(argv[0], "cd") == 0
		|| ft_strcmp(argv[0], "echo") == 0
		|| ft_strcmp(argv[0], "pwd") == 0)
		return (TRUE);
	return (FALSE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:49:45 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/07 17:06:51 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_simple_command *command, t_map *envmap)
{
	int		status;
	char	**argv;

	status = 0;
	argv = tokens_to_argv(command->arguments);
	if (ft_strcmp(argv[0], "env") == 0)
		status = builtin_env(argv, envmap);
	free_array(argv);
	return (status);
}

int	is_builtin(void)
{
	return (0);
}

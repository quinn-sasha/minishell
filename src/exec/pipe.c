/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:23:29 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/07 16:34:22 by yurishik         ###   ########.fr       */
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

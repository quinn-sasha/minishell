/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:52:45 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/21 17:15:25 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command_args_empty(t_simple_command *command)
{
	t_token	*args;

	if (command == NULL)
		return (TRUE);
	args = command->arguments;
	if (args == NULL)
		return (TRUE);
	if (args->token_kind == TOKEN_EOF || args->word == NULL)
		return (TRUE);
	return (FALSE);
}

void	execute_empty_command(t_simple_command *command)
{
	if (open_redirect_file(command->redirect) == FAILED)
		exit(1);
	do_redirect(command->redirect);
	reset_redirect(command->redirect);
	exit(0);
}

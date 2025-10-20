/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:19:56 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 14:39:08 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
<command_element> = <word> | <redirection>
<redirection> = '>' <word>
              | '<' <word>
              | '>>' <word>
              | '<<' <word>
*/
void	append_command_element(t_simple_command *command,
		t_token **token_to_return, t_token *token)
{
	t_redirect	*redirect;

	if (token->token_kind == TOKEN_WORD)
	{
		append_token(&command->arguments, duplicate_token(token));
		*token_to_return = token->next;
		return ;
	}
	redirect = new_redirect(token);
	append_redirect(&command->redirect, redirect);
	*token_to_return = token->next->next;
}

/*
* @param: token to advance until it reaches EOF or pipe.
*         The change will be reflected at caller.
* @param: token
* @return: One simple command
* It creates one simple command.
*/
t_simple_command	*make_simple_command(t_token **token_to_return,
		t_token *token)
{
	t_simple_command	*command;
	t_token				*tail;

	command = xcalloc(1, sizeof(t_simple_command));
	while (!at_eof(token) && !is_same_operator(token, PIPE_SYMBOL))
	{
		append_command_element(command, &token, token);
	}
	tail = new_token(TOKEN_EOF, NULL);
	append_token(&command->arguments, tail);
	*token_to_return = token;
	command->inpipe[0] = STDIN_FILENO;
	command->inpipe[1] = -1;
	command->outpipe[0] = -1;
	command->outpipe[1] = STDOUT_FILENO;
	return (command);
}

/*
* @param: valid token
* @return: simple command list. operators are removed.
* Make simple command from valid token.
* However, child pid is not assigned in this function,
* but later in prepare_pipeline().
*/
t_simple_command	*make_simple_command_list(t_token *token)
{
	t_simple_command	*command;

	if (token->token_kind == TOKEN_EOF)
		return (NULL);
	command = make_simple_command(&token, token);
	if (is_same_operator(token, PIPE_SYMBOL))
	{
		command->next = make_simple_command_list(token->next);
	}
	return (command);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:19:59 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 14:37:49 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
How to interpret input.

<pipeline> = <simple_command> ('|' <pipeline>)
<simple_command> = <command_element>+
<command_element> = <word> | <redirection>
<redirection> = '>' <word>
              | '<' <word>
              | '>>' <word>
              | '<<' <word>
*/
bool	is_same_operator(t_token *token, char *operator)
{
	if (token->token_kind != TOKEN_OPERATOR)
		return (false);
	if (ft_strcmp(token->word, operator) == 0)
		return (true);
	return (false);
}

bool	is_valid_syntax(t_token *token)
{
	if (is_same_operator(token, PIPE_SYMBOL))
	{
		syntax_error(token->word);
		return (false);
	}
	while (!at_eof(token))
	{
		if (token->token_kind == TOKEN_WORD)
		{
			token = token->next;
			continue ;
		}
		if (token->next->token_kind == TOKEN_EOF)
		{
			syntax_error("newline");
			return (false);
		}
		if (is_same_operator(token, PIPE_SYMBOL)
			&& is_same_operator(token->next, PIPE_SYMBOL))
		{
			syntax_error(token->word);
			return (false);
		}
		if (!is_same_operator(token, PIPE_SYMBOL)
			&& token->next->token_kind == TOKEN_OPERATOR)
		{
			syntax_error(token->next->word);
			return (false);
		}
		token = token->next;
	}
	return (true);
}

int	parse(t_simple_command **command, t_token *token)
{
	if (!is_valid_syntax(token))
	{
		free_token_list(token);
		return (PARSE_SYNTAX_ERROR);
	}
	*command = make_simple_command_list(token);
	free_token_list(token);
	return (PARSE_SUCCESS);
}

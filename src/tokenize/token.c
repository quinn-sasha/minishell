/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:20:10 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 15:21:44 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	at_eof(t_token *token)
{
	if (token == NULL)
		return (false);
	return (token->token_kind == TOKEN_EOF);
}

t_token	*new_token(t_token_kind token_kind, char *word)
{
	t_token	*new_token;

	new_token = xcalloc(1, sizeof(t_token));
	new_token->token_kind = token_kind;
	new_token->word = word;
	new_token->is_quoted = false;
	new_token->is_expanded = false;
	new_token->next = NULL;
	return (new_token);
}

t_token	*duplicate_token(t_token *token)
{
	char	*word;
	t_token	*result;

	word = xstrdup(token->word);
	result = new_token(token->token_kind, word);
	result->is_quoted = token->is_quoted;
	return (result);
}

void	append_token(t_token **head, t_token *element)
{
	t_token	*iter;

	if (*head == NULL)
	{
		*head = element;
		return ;
	}
	iter = *head;
	while (iter->next)
	{
		iter = iter->next;
	}
	iter->next = element;
}

void	insert_next_token(t_token *token, t_token *new_token)
{
	new_token->next = token->next;
	token->next = new_token;
}

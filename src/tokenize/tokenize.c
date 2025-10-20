/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:20:13 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 18:34:42 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
blank
  A space or tab character.

control operator
  A token that performs a control function. It is a newline or '|'.

metacharacter
  A character that, when unquoted, separates words. A metacharacter is
  a space, tab, newline, or one of the following characters: '|', '<', or '>'.

token
  A sequence of characters considered a single unit by the shell.
  It is either a word or an operator.

operator
  A control operator or a redirection operator. See Redirections, for a list of
  redirection operators. Operators contain at least one unquoted metacharacter.

word
  A sequence of characters treated as a unit by the shell.
  Words may not include unquoted metacharacters.
*/
char	get_quote_marker(int quote)
{
	if (quote == SINGLE_QUOTE_CHARCTER)
		return (SINGLE_QUOTE_MARKER);
	return (DOUBLE_QUOTE_MARKER);
}

void	replace_quote_char_with_marker(char **input_to_modify, char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (!is_quote(input[i]))
		{
			i++;
			continue ;
		}
		quote = input[i];
		(*input_to_modify)[i] = get_quote_marker(quote);
		i++;
		while (input[i] != quote)
			i++;
		(*input_to_modify)[i] = get_quote_marker(quote);
		i++;
	}
}

size_t	count_token(t_token *token)
{
	size_t	i;
	t_token	*current;

	if (token == NULL)
		return (0);
	i = 0;
	current = token;
	while (current->token_kind != TOKEN_EOF)
	{
		i++;
		current = current->next;
	}
	return (i);
}

static void build_token_list(t_token *token, char *input) {
	while (*input) {
		if (is_blank(*input)) {
			input++;
			continue;
		}
		if (is_metacharacter(*input)) {
			token->next = consume_operator(&input, input);
			token = token->next;
			continue;
		}
		token->next = consume_word(&input, input);
		token = token->next;
	}
	token->next = new_token(TOKEN_EOF, NULL);
}

t_token	*tokenize(char *input)
{
	t_token	dummy;

	if (!is_quote_closed(input))
	{
		unclosed_quote_error();
		return (NULL);
	}
	replace_quote_char_with_marker(&input, input);
	dummy.next = NULL;
	build_token_list(&dummy, input);
	return (dummy.next);
}

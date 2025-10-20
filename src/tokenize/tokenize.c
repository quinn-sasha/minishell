/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:20:13 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 14:34:22 by yurishik         ###   ########.fr       */
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
int	is_blank(int c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

bool	is_quote_marker(int c)
{
	if (c == SINGLE_QUOTE_MARKER)
		return (true);
	if (c == DOUBLE_QUOTE_MARKER)
		return (true);
	return (false);
}

bool	is_quote(int c)
{
	if (is_quote_marker(c))
		return (true);
	if (c == SINGLE_QUOTE_CHARCTER)
		return (true);
	if (c == DOUBLE_QUOTE_CHARACTER)
		return (true);
	return (false);
}

int	is_metacharacter(int c)
{
	if (is_blank(c))
		return (true);
	return (ft_strchr("|<>", c) != NOT_FOUND);
}

t_token	*consume_operator(char **input_to_return, char *input)
{
	static const char	*operators[] = {"<<", ">>", "<", ">", "|", NULL};
	int					i;
	char				*word;
	t_token				*result;

	i = 0;
	while (operators[i])
	{
		if (ft_strncmp(input, operators[i], ft_strlen(operators[i])) != 0)
		{
			i++;
			continue ;
		}
		word = ft_strdup(operators[i]);
		result = new_token(TOKEN_OPERATOR, word);
		*input_to_return += ft_strlen(operators[i]);
		return (result);
	}
	return (NULL);
}

void	consume_quoted_word(char **input_to_return, char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = input[i];
	i++;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] == '\0')
		assert_error("Word is not quoted");
	i++;
	*input_to_return += i;
}

t_token	*consume_word(char **input_to_return, char *input)
{
	bool	is_quoted_flag;
	char	*c_ptr;
	char	*word;
	t_token	*result;

	is_quoted_flag = false;
	c_ptr = input;
	while (*c_ptr)
	{
		if (is_metacharacter(*c_ptr))
			break ;
		if (!is_quote(*c_ptr))
		{
			c_ptr++;
			continue ;
		}
		consume_quoted_word(&c_ptr, c_ptr);
		is_quoted_flag = true;
	}
	word = ft_substr(input, 0, c_ptr - input - 1);
	result = new_token(TOKEN_WORD, word);
	result->is_quoted = is_quoted_flag;
	*input_to_return = c_ptr;
	return (result);
}

bool	is_quote_closed(char *input)
{
	char	quote_to_match;

	while (*input)
	{
		if (!is_quote(*input))
		{
			input++;
			continue ;
		}
		quote_to_match = *input;
		input++;
		while (*input && *input != quote_to_match)
		{
			input++;
		}
		if (*input == '\0')
			return (false);
		input++;
	}
	return (true);
}

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

t_token	*tokenize(char *input)
{
	t_token	dummy;
	t_token	*token;

	dummy.next = NULL;
	token = &dummy;
	if (!is_quote_closed(input))
	{
		unclosed_quote_error();
		return (NULL);
	}
	replace_quote_char_with_marker(&input, input);
	while (*input)
	{
		if (is_blank(*input))
		{
			input++;
			continue ;
		}
		if (is_metacharacter(*input))
		{
			token->next = consume_operator(&input, input);
			token = token->next;
			continue ;
		}
		token->next = consume_word(&input, input);
		token = token->next;
	}
	token->next = new_token(TOKEN_EOF, NULL);
	return (dummy.next);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:20:13 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 15:21:42 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

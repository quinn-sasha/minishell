/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token_words.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:16:47 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 14:39:47 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_default_ifs(int c)
{
	if (c == ' ')
		return (true);
	if (c == '\t')
		return (true);
	if (c == '\n')
		return (true);
	return (false);
}

static int	get_word_end(const char *s, int start)
{
	int		i;
	char	quote;

	if (is_default_ifs(s[start]))
		assert_error(
			"get_word_end(): first character of word is IFS character");
	i = start;
	while (s[i])
	{
		if (is_default_ifs(s[i]))
			return (i);
		if (!is_quote_marker(s[i]))
		{
			i++;
			continue ;
		}
		quote = s[i];
		i++;
		while (s[i] != quote)
			i++;
		i++;
	}
	return (i);
}

void	split_token_word(t_token *token)
{
	char	*trimmed;
	char	*to_free;
	int		start;
	int		end;

	trimmed = ft_strtrim(token->word, DEFAULT_IFS_CHARS);
	if (*trimmed == '\0')
	{
		free(trimmed);
		free(token->word);
		token->word = NULL;
		return ;
	}
	to_free = token->word;
	start = 0;
	while (trimmed[start])
	{
		if (is_default_ifs(trimmed[start]))
		{
			start++;
			continue ;
		}
		end = get_word_end(trimmed, start);
		token->word = ft_substr(trimmed, start, end - 1);
		insert_next_token(token, new_token(TOKEN_WORD, NULL));
		token->next->is_quoted = token->is_quoted;
		token = token->next;
		start = end;
	}
	free(trimmed);
	free(to_free);
}

void	split_token_words(t_token *token)
{
	t_token	*iter;

	iter = token;
	while (!at_eof(iter))
	{
		if (!iter->is_expanded)
		{
			iter = iter->next;
			continue ;
		}
		split_token_word(iter);
		iter = iter->next;
	}
}

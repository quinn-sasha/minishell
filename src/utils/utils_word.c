/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:19:37 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 15:09:28 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_in_set(char letter, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == letter)
			return (1);
		i++;
	}
	return (0);
}

int	count_words(char *s, const char *excluded_chars)
{
	int	result;

	if (*s == '\0')
		return (0);
	result = 0;
	while (*s)
	{
		if (is_in_set(*s, excluded_chars))
		{
			s++;
			continue ;
		}
		if (is_quote(*s))
		{
			consume_quoted_word(&s, s);
			continue ;
		}
		while (*s && !is_in_set(*s, excluded_chars))
			s++;
		result++;
	}
	return (result);
}

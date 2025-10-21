/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:15:51 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 20:15:25 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	need_to_expand(char *word)
{
	char	*c_ptr;

	if (ft_strchr(word, '$') == NOT_FOUND)
		return (false);
	c_ptr = word;
	while (*c_ptr)
	{
		if (*c_ptr == SINGLE_QUOTE_MARKER)
		{
			consume_quoted_word(&c_ptr, c_ptr);
			continue ;
		}
		if (*c_ptr != '$')
		{
			c_ptr++;
			continue ;
		}
		if (is_special_parameter(c_ptr))
			return (true);
		if (is_alpha_underscore(*(c_ptr + 1)))
			return (true);
		c_ptr++;
	}
	return (false);
}

void	append_single_quoted_word(char **dest, char *src)
{
	int	i;

	i = 0;
	if (src[i] != SINGLE_QUOTE_MARKER)
		assert_error("Expected single quote");
	append_character(dest, src[i]);
	i++;
	while (src[i] != SINGLE_QUOTE_MARKER)
	{
		if (src[i] == '\0')
			assert_error("Unclosed single quote");
		append_character(dest, src[i]);
		i++;
	}
	append_character(dest, src[i]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 21:34:20 by squinn            #+#    #+#             */
/*   Updated: 2025/10/20 22:01:09 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_single_quote(char **new_word, char **char_ptr_to_return,
		char *char_ptr)
{
	append_single_quoted_word(new_word, char_ptr);
	consume_quoted_word(char_ptr_to_return, char_ptr);
}

static char	*expand_word_helper(char *char_ptr, t_map *envmap)
{
	char	*new_word;

	new_word = xcalloc(1, sizeof(char));
	while (*char_ptr)
	{
		if (*char_ptr == SINGLE_QUOTE_MARKER)
		{
			handle_single_quote(&new_word, &char_ptr, char_ptr);
			continue ;
		}
		if (*char_ptr != '$')
		{
			append_character(&new_word, *char_ptr);
			char_ptr++;
			continue ;
		}
		if (is_special_parameter(char_ptr))
		{
			expand_special_parameter(&new_word, &char_ptr, char_ptr,
				envmap->last_status);
			continue ;
		}
		expand_parameter(&new_word, &char_ptr, char_ptr, envmap);
	}
	return (new_word);
}

void	expand_word(char **word, t_map *envmap)
{
	char	*new_word;

	new_word = expand_word_helper(*word, envmap);
	free(*word);
	*word = new_word;
}

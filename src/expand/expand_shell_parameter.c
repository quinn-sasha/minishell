/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_shell_parameter.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:15:51 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 14:39:36 by yurishik         ###   ########.fr       */
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

void	expand_parameter(char **new_word, char **char_ptr_to_return,
		char *char_ptr, t_map *envmap)
{
	char	*name;
	char	*expanded;

	char_ptr++;
	if (!is_alpha_underscore(*char_ptr))
	{
		assert_error(
			"Invalid variable was not to be exapanded,"
			" but now in expand_parameter()"
			);
	}
	name = xcalloc(1, sizeof(char));
	while (is_alpha_underscore_num(*char_ptr))
	{
		append_character(&name, *char_ptr);
		char_ptr++;
	}
	*char_ptr_to_return = char_ptr;
	expanded = xgetenv(envmap, name);
	free(name);
	if (expanded == NULL)
	{
		return ;
	}
	append_string_to_string(new_word, expanded);
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

void	expand_word(char **word, t_map *envmap)
{
	char	*new_word;
	char	*char_ptr;

	new_word = xcalloc(1, sizeof(char));
	char_ptr = *word;
	while (*char_ptr)
	{
		if (*char_ptr == SINGLE_QUOTE_MARKER)
		{
			append_single_quoted_word(&new_word, char_ptr);
			consume_quoted_word(&char_ptr, char_ptr);
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
	free(*word);
	*word = new_word;
}

void	expand_token_words(t_token *token, t_map *envmap)
{
	while (!at_eof(token))
	{
		if (need_to_expand(token->word))
		{
			expand_word(&token->word, envmap);
			token->is_expanded = true;
		}
		token = token->next;
	}
}

void	expand_redirect_words(t_redirect *redirect, t_map *envmap)
{
	while (redirect)
	{
		if (redirect->redirect_kind == r_reading_until)
		{
			redirect = redirect->next;
			continue ;
		}
		if (need_to_expand(redirect->to.filename))
		{
			expand_word(&(redirect->to.filename), envmap);
			redirect->is_filename_expanded = true;
		}
		redirect = redirect->next;
	}
}

void	expand_shell_parameter(t_simple_command *command, t_map *envmap)
{
	t_simple_command	*iter;

	iter = command;
	while (iter)
	{
		expand_token_words(iter->arguments, envmap);
		expand_redirect_words(iter->redirect, envmap);
		iter = iter->next;
	}
}

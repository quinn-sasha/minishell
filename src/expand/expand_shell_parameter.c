/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_shell_parameter.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:15:51 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 21:34:11 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:16:43 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 09:16:43 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quote_word(char **word_to_modify)
{
	char	*new_word;
	char	*old_word;
	int		i;

	new_word = xcalloc(1, sizeof(char));
	old_word = *word_to_modify;
	i = 0;
	while (old_word[i])
	{
		if (is_quote_marker(old_word[i]))
		{
			i++;
			continue ;
		}
		append_character(&new_word, old_word[i]);
		i++;
	}
	free(old_word);
	*word_to_modify = new_word;
}

void	remove_quote_token(t_token *token)
{
	t_token	*iter;

	if (token == NULL)
		return ;
	iter = token;
	while (!at_eof(iter))
	{
		if (!iter->is_quoted)
		{
			iter = iter->next;
			continue ;
		}
		remove_quote_word(&iter->word);
		iter = iter->next;
	}
}

void	remove_quote_redirect(t_redirect *redirect)
{
	t_redirect	*iter;

	if (redirect == NULL)
		return ;
	iter = redirect;
	while (iter)
	{
		if (!iter->is_filename_quoted)
		{
			iter = iter->next;
			continue ;
		}
		if (iter->redirect_kind == r_reading_until)
			remove_quote_word(&iter->here_doc_eof);
		else
			remove_quote_word(&iter->to.filename);
		iter = iter->next;
	}
}

void	remove_quote(t_simple_command *command)
{
	remove_quote_token(command->arguments);
	remove_quote_redirect(command->redirect);
}

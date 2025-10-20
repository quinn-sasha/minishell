/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:16:49 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 14:39:57 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_redirect_filename(t_redirect *redirect)
{
	t_redirect	*iter;
	char		*old_filename;
	char		*trimmed;

	iter = redirect;
	while (iter)
	{
		if (!iter->is_filename_expanded)
		{
			iter = iter->next;
			continue ;
		}
		old_filename = redirect->to.filename;
		trimmed = ft_strtrim(old_filename, DEFAULT_IFS_CHARS);
		redirect->to.filename = trimmed;
		free(old_filename);
	}
}

static void	remove_unnecessary_tail_token(t_token **token)
{
	t_token	*temp;
	t_token	*iter;
	t_token	*to_remove;

	while (!at_eof(*token) && (*token)->word == NULL)
	{
		temp = *token;
		*token = (*token)->next;
		free(temp);
	}
	if (at_eof(*token))
		return ;
	iter = *token;
	while (!at_eof(iter) && !at_eof(iter->next))
	{
		if (iter->next->word != NULL)
		{
			iter = iter->next;
			continue ;
		}
		to_remove = iter->next;
		iter->next = iter->next->next;
		free(to_remove);
	}
}

void	split_words(t_simple_command *command)
{
	split_token_words(command->arguments);
	remove_unnecessary_tail_token(&command->arguments);
	trim_redirect_filename(command->redirect);
}

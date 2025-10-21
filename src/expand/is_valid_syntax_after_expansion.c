/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_syntax_after_expansion.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:16:41 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 09:16:41 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_filename(const char *filename)
{
	char	*ifs_trimmed;
	int		num_words;

	if (*filename == '\0')
		return (false);
	ifs_trimmed = ft_strtrim(filename, DEFAULT_IFS_CHARS);
	if (*ifs_trimmed == '\0')
	{
		free(ifs_trimmed);
		return (false);
	}
	num_words = count_words(ifs_trimmed, DEFAULT_IFS_CHARS);
	free(ifs_trimmed);
	if (num_words != 1)
		return (false);
	return (true);
}

int	is_valid_syntax_after_expansion(t_redirect *redirect)
{
	t_redirect	*iter;
	char		*filename;

	if (redirect == NULL)
		return (true);
	iter = redirect;
	while (iter)
	{
		if (!iter->is_filename_expanded)
		{
			iter = iter->next;
			continue ;
		}
		filename = iter->to.filename;
		if (!is_valid_filename(filename))
		{
			return (false);
		}
		iter = iter->next;
	}
	return (true);
}

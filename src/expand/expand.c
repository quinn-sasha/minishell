/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:16:38 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 09:16:38 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_character(char **string, int c)
{
	char	*new_string;
	size_t	new_length;

	if (*string == NULL)
	{
		new_string = xcalloc(2, sizeof(char));
		new_string[0] = c;
		*string = new_string;
		return ;
	}
	new_length = ft_strlen(*string) + 1;
	new_string = xcalloc(new_length + 1, sizeof(char));
	ft_strlcpy(new_string, *string, new_length + 1);
	new_string[new_length - 1] = c;
	free(*string);
	*string = new_string;
}

void	append_string_to_string(char **dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		append_character(dest, src[i]);
		i++;
	}
}

/*
* @return: 展開して文法エラーが発生したら EXPAND_SYNTAX_ERROR を返す.
           それ以外は EXPAND_SUCESS
*/
int	expand(t_simple_command *command, t_map *envmap)
{
	expand_shell_parameter(command, envmap);
	if (!is_valid_syntax_after_expansion(command->redirect))
	{
		ambiguous_redirect_error();
		return (EXPAND_SYNTAX_ERROR);
	}
	split_words(command);
	remove_quote(command);
	return (EXPAND_SUCCESS);
}

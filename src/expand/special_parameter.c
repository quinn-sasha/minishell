/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_parameter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:16:45 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 09:43:51 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_special_parameter(const char *s)
{
	return (s[0] == '$' && s[1] == '?');
}

void	append_num_to_string(char **dest, unsigned int num)
{
	char	*converted;
	int		i;

	if (num < 10)
	{
		append_character(dest, num + '0');
		return ;
	}
	converted = unsigned_itoa(num, 10);
	i = 0;
	while (converted[i])
	{
		append_character(dest, converted[i]);
		i++;
	}
}

void	expand_special_parameter(char **new_word, char **char_ptr_to_return,
		char *char_ptr, int last_status)
{
	if (last_status < 0)
		assert_error("last status should not be negative");
	append_num_to_string(new_word, last_status);
	char_ptr += 2;
	*char_ptr_to_return = char_ptr;
}

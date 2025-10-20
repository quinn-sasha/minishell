/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_identifier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:29:49 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 08:29:50 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_alpha_underscore(int c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_alpha_underscore_num(int c)
{
	return (is_alpha_underscore(c) || ft_isdigit(c));
}

bool	is_identifier(const char *s)
{
	if (s == NULL)
	{
		return (false);
	}
	if (!is_alpha_underscore(*s))
	{
		return (false);
	}
	while (*s)
	{
		if (!is_alpha_underscore_num(*s))
		{
			return (false);
		}
		s++;
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstrdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:26:33 by squinn            #+#    #+#             */
/*   Updated: 2025/09/16 19:14:16 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*xstrdup(const char *s)
{
	char	*result;

	result = ft_strdup(s);
	if (result == NULL)
	{
		fatal_error("xstrdup()");
	}
	return (result);
}

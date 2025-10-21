/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:31:31 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 15:12:17 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prefix_error(void)
{
	ft_putstr_fd(PREFIX_ERROR, STDERR_FILENO);
}

void	unclosed_quote_error(void)
{
	prefix_error();
	ft_dprintf(STDERR_FILENO, "syntax error: unclosed quote\n");
}

void	syntax_error(const char *unexpected_token)
{
	prefix_error();
	ft_dprintf(STDERR_FILENO, "syntax error near unexpected token: %s\n",
		unexpected_token);
}

void	ambiguous_redirect_error(void)
{
	prefix_error();
	ft_dprintf(STDERR_FILENO, "ambiguous redirect\n");
}

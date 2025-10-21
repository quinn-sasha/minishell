/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:51:24 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/21 14:27:49 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n_option(char *str)
{
	int	i;

	if (str[0] != '-')
		return (FALSE);
	i = 1;
	while (str[i] == 'n')
	{
		i++;
	}
	if (str[i] != '\0')
		return (FALSE);
	return (TRUE);
}

int	builtin_echo(char **argv)
{
	int		is_first_arg;
	int		flg_newline;
	size_t	i;

	i = 1;
	flg_newline = TRUE;
	while (argv[i] && is_n_option(argv[i]) == TRUE)
	{
		flg_newline = FALSE;
		i++;
	}
	is_first_arg = TRUE;
	while (argv[i])
	{
		if (is_first_arg == FALSE)
			ft_dprintf(STDOUT_FILENO, " ");
		is_first_arg = FALSE;
		ft_dprintf(STDOUT_FILENO, argv[i]);
		i++;
	}
	if (flg_newline == TRUE)
		ft_dprintf(STDOUT_FILENO, "\n");
	return (SUCCESS);
}

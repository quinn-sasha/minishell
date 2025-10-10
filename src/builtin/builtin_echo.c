/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:51:24 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/10 16:42:56 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **argv)
{
	int		is_first_arg;
	int		flg_newline;
	size_t	i;

	i = 1;
	flg_newline = TRUE;
	if (argv[1] && ft_strncmp(argv[1], "-n", 3) == 0)
	{
		i++;
		flg_newline = FALSE;
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
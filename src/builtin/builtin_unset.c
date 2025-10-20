/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:24:13 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 14:35:00 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **argv, t_map *envmap)
{
	char	*name;
	int		i;
	int		status;

	if (envmap == NULL)
		return (FAILED);
	status = SUCCESS;
	i = 1;
	while (argv[i] != NULL)
	{
		name = argv[i];
		if (!is_identifier(name))
		{
			perror_wrapper("unset", name, "not a valid identifier");
			status = 1;
			i++;
			continue ;
		}
		map_delete(envmap, name);
		i++;
	}
	return (status);
}

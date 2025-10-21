/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:24:13 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/21 13:37:33 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **argv, t_map *envmap)
{
	char	*name;
	int		i;

	if (envmap == NULL)
		return (FAILED);
	i = 1;
	while (argv[i] != NULL)
	{
		name = argv[i];
		if (!is_identifier(name))
		{
			perror_wrapper("unset", name, "not a valid identifier");
			i++;
			continue ;
		}
		map_delete(envmap, name);
		i++;
	}
	return (SUCCESS);
}

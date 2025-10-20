/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:29:41 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 08:29:43 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_map	*init_environment(void)
{
	extern char	**environ;
	t_map		*envmap;
	int			i;
	char		cwd[PATH_MAX];

	envmap = xcalloc(1, sizeof(t_map));
	i = 0;
	while (environ[i])
	{
		map_set(envmap, environ[i], TRUE);
		i++;
	}
	if (map_get(envmap, "PWD") == NULL)
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
			perror_wrapper("init_envmap()", "get_cwd()", NULL);
		else
			map_set_internal(envmap, "PWD", cwd, FALSE);
	}
	map_set_internal(envmap, "OLDPWD", NULL, TRUE);
	return (envmap);
}

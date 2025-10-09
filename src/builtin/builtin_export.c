/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:51:24 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/09 19:42:56 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(char **argv, t_map *envmap)
{
	char	*name;
	char	*value;
	int		status;
	char	*str;
	t_item	*current;

	if (argv[1] == NULL)
		return (builtin_env(envmap)); // TODO // ABC順に一覧表示させる
	str = argv[1];
	status = SUCCESS;
	set_name_and_value(str, &name, &value);
	current = map_get(envmap, name);
	if (current != NULL && value != NULL)
		map_update_item(current, value);
	else if (current == NULL)
		map_insert(envmap, name, value);
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:51:24 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/21 17:08:54 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_export_string(char *name, char *value, t_map *envmap)
{
	char	*final_value;

	if (value == NULL)
	{
		final_value = xgetenv(envmap, name);
		if (final_value != NULL)
			return (join_str_separator(name, final_value, '='));
		else
			return (xstrdup(name));
	}
	return (join_str_separator(name, value, '='));
}

int	free_and_return_status(char *name, char *value, int status)
{
	if (name)
		free(name);
	if (value)
		free(value);
	return (status);
}

int	process_export_argument(char *arg, t_map *envmap)
{
	char	*name;
	char	*value;
	char	*export_str;
	int		status;

	status = SUCCESS;
	set_name_and_value(arg, &name, &value);
	if (!is_identifier(name))
	{
		perror_wrapper("export", name, "not a valid identifier");
		status = 1;
		return (free_and_return_status(name, value, status));
	}
	export_str = create_export_string(name, value, envmap);
	if (!export_str)
	{
		return (free_and_return_status(name, value, 1));
	}
	map_set(envmap, export_str, TRUE);
	free(export_str);
	return (free_and_return_status(name, value, status));
}

int	builtin_export(char **argv, t_map *envmap)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (argv[1] == NULL)
		return (display_map_ordered(envmap));
	while (argv[i] != NULL)
	{
		if (process_export_argument(argv[i], envmap) == 1)
			status = 1;
		i++;
	}
	return (status);
}

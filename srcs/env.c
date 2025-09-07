/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 08:21:22 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/08 08:51:35 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_env(char ***dest, char **environ)
{
	int		i;
	int		count;
	char	**result;

	count = 0;
	while (environ[count])
		count++;
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (1);
	i = 0;
	while (i < count)
	{
		if (ft_strndup(environ[i], ft_strlen(environ[i]), &result[i]) != 0)
		{
			free_str_array(result);
			return (1);
		}
		i++;
	}
	result[i] = NULL;
	*dest = result;
	return (0);
}

int	initialize_environ(t_environ *env, char **environ)
{
	if (copy_env(&env->env, environ) == -1)
		return (-1);
	env->last_status = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:51:24 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/02 13:51:41 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// USER=yurishikみたいな文字列が来たらUSERというkeyを取得するための関数
char	*get_key(char *str)
{
	int		len;
	char	*key;

	len = get_key_length(str);
	if (ft_strndup(str, len, &key) == FAILURE)
	{
		return (NULL);
	}
	return (key);
}

char	*get_value(char *str)
{
	int		key_len;
	int		len;
	char	*value;

	key_len = get_key_length(str);
	if (key_len == -1)
		return (NULL);
	len = ft_strlen(str);
	if (ft_strndup(str + key_len + 1, len - key_len - 1, &value) == FAILURE)
		return (NULL);
	return (value);
}

int	builtin_export(t_env **env, char *str)
{
	char	*key;
	char	*value;
	int		status;

	status = SUCCESS;
	key = get_key(str);
	if (key == NULL)
		return (FAILURE);
	value = get_value(str);
	if (value == NULL)
	{
		free(key);
		return (FAILURE);
	}
	if (find_env(*env, key) == NULL)
		env_lstadd_back(env, env_lstnew(str));
	else if (update_env(env, key, value) == FAILURE)
		status = FAILURE;
	free(key);
	free(value);
	return (status);
}

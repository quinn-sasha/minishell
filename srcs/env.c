/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:14:54 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/02 15:28:47 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief  (minishell起動時に)environから環境変数の構造体にコピーする
 *
 * @author yurishik
 * @param dest t_envのLinked List
 * @param environ externしたenviron
 * @return 正常終了すればSUCCESS, エラーがあればFAILURE
 */
int	initialize_environ(t_env **dest, char **environ)
{
	int		i;
	t_env	*new_node;

	if (dest == NULL || environ == NULL)
		return (FAILURE);
	*dest = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		new_node = env_lstnew(environ[i]);
		if (new_node == NULL)
		{
			env_lstfree(*dest);
			return (FAILURE);
		}
		env_lstadd_back(dest, new_node);
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief 環境変数を名前で指定して検索する
 *
 * @author yurishik
 * @param head t_envのLinked Listの先頭
 * @param key 検索したいkey
 * @return 指定したkeyの環境変数が存在すればそのvalue、なければ空文字
 */
char	*find_env(t_env *head, const char *key)
{
	t_env	*current;
	size_t	key_len;

	if (head == NULL || key == NULL)
		return (NULL);
	key_len = ft_strlen(key);
	current = head;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, key, key_len) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	update_env(t_env **head, char *key, char *value)
{
	t_env	*current;
	size_t	key_len;

	if (head == NULL || key == NULL)
		return (FAILURE);
	key_len = ft_strlen(key);
	current = *head;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, key, key_len) == 0)
		{
			free(current->value);
			if (ft_strndup(value, ft_strlen(value), &current->value) == FAILURE)
				return (FAILURE);
			return (SUCCESS);
		}
		current = current->next;
	}
	return (FAILURE);
}

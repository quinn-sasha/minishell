/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:14:54 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/16 16:56:29 by yurishik         ###   ########.fr       */
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
 * @brief 環境変数を名前で指定してunsetする
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
		return ("");
	key_len = ft_strlen(key);
	current = head;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, key, key_len) == 0)
			return (current->value);
		current = current->next;
	}
	return ("");
}

/**
 * @brief 環境変数名として問題ないかのvalid (TODO: 使える文字種かどうかを確認する部分を追記)
 *
 * @author yurishik
 * @param name チェックしたい文字列
 * @return 環境変数名としてOKならFLG_TRUE, NGならFLG_FALSE
 */
int	is_env_key_name(const char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len <= 0)
		return (FLG_FALSE);
	return (FLG_TRUE);
}

/**
 * @brief unset_envのnorminette対応用
 */
void	unset_mid_node(t_env *prev, t_env *current)
{
	if (current != NULL)
	{
		prev->next = current->next;
		env_delone(current);
	}
}

/**
 * @brief 環境変数を名前で指定してunsetする
 *
 * @author yurishik
 * @param head t_envのLinked Listの先頭
 * @param name unsetしたい環境変数名
 * @return 環境変数名としてOKならFLG_TRUE, NGならFLG_FALSE
 */
int	unset_env(t_env **head, const char *name)
{
	t_env	*current;
	t_env	*prev;

	if (head == NULL || name == NULL)
		return (FAILURE);
	if (*head != NULL && ft_strcmp((*head)->key, name) == 0)
	{
		current = *head;
		*head = current->next;
		env_delone(current);
		return (SUCCESS);
	}
	prev = *head;
	if (prev == NULL)
		return (SUCCESS);
	current = prev->next;
	while (current != NULL && ft_strcmp(current->key, name) != 0)
	{
		prev = current;
		current = current->next;
	}
	unset_mid_node(prev, current);
	return (SUCCESS);
}

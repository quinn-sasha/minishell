/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:14:54 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/16 15:31:40 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			free_env_list(*dest);
			return (FAILURE);
		}
		env_lstadd_back(dest, new_node);
		i++;
	}
	return (SUCCESS);
}

t_env	*find_env_node(t_env *head, const char *key)
{
	t_env	*current;
	size_t	key_len;

	if (head == NULL || key == NULL)
		return (NULL);
	key_len = ft_strlen(key);
	current = head;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, key, key_len) == 0 && \
			ft_strlen(current->key) == key_len)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	is_env_key_name(const char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len <= 0)
		return (FLG_FALSE);
	return (FLG_TRUE);
}

void	unset_mid_node(t_env *prev, t_env *current)
{
	if (current != NULL)
	{
		prev->next = current->next;
		env_delone(current);
	}
}

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

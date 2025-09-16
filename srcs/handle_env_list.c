/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:16:35 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/16 15:20:46 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_value(t_env *new_node, char *str, int key_len)
{
	int	value_len;

	value_len = ft_strlen(str) - key_len - 1;
	if (ft_strndup(str + key_len + 1, value_len, &new_node->value) == FAILURE)
	{
		free(new_node->key);
		free(new_node);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_env	*env_lstnew(char *str)
{
	t_env	*new_node;
	int		key_len;

	key_len = get_key_length(str);
	if (key_len == -1)
		return (NULL);
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	if (ft_strndup(str, key_len, &new_node->key) == FAILURE)
	{
		free(new_node);
		return (NULL);
	}
	if (create_value(new_node, str, key_len) == FAILURE)
		return (NULL);
	new_node->next = NULL;
	return (new_node);
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*current;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

void	free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	env_delone(t_env *lst)
{
	if (lst == NULL)
		return ;
	if (lst->key)
		free(lst->key);
	if (lst->value)
		free(lst->value);
	free(lst);
}

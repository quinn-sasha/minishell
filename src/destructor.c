/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:19:34 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 09:19:34 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token *token)
{
	t_token	*next;

	while (!at_eof(token))
	{
		next = token->next;
		free(token->word);
		free(token);
		token = next;
	}
	free(token);
}

/*
* @brief redirect構造体リストを解放する. 解放後にNULLは代入しない.
*        理由は、redirectにアクセスするための command 構造体が解放後に NULL 代入されるから.
*/
void	clean_redirect(t_redirect *redirect)
{
	t_redirect	*next;

	if (redirect == NULL)
		return ;
	next = redirect->next;
	if (redirect->redirect_kind == r_reading_until)
	{
		free(redirect->here_doc_eof);
		free(redirect);
		clean_redirect(next);
		return ;
	}
	free(redirect->to.filename);
	free(redirect);
	clean_redirect(next);
}

void	clean_environment(t_map *envmap)
{
	t_item	*node;
	t_item	*next;

	node = envmap->head.next;
	while (node)
	{
		next = node->next;
		free(node->name);
		free(node->value);
		free(node);
		node = next;
	}
	free(envmap);
}

/*
* @brief 動的に割り当てたコマンド構造体のリストを解放する. 解放後は NULL を代入する.
*/
void	clean_command(t_simple_command **command)
{
	t_simple_command	*next;

	if (*command == NULL)
	{
		return ;
	}
	next = (*command)->next;
	if ((*command)->arguments)
	{
		free_token_list((*command)->arguments);
	}
	if ((*command)->redirect)
	{
		clean_redirect((*command)->redirect);
	}
	free(*command);
	*command = NULL;
	clean_command(&next);
}

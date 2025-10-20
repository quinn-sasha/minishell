/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:20:01 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 09:22:54 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
redirectの種類から、redirect構造体のメンバに値を書き込む.
*/
void	fill_redirect(t_redirect *redirect, t_redirect_kind r_kind,
			t_token *token)
{
	char	*filename;

	redirect->redirect_kind = r_kind;
	if (r_kind == r_input_direction)
	{
		redirect->from.fd = STDIN_FILENO;
		filename = xstrdup(token->next->word);
		redirect->is_filename_quoted = token->next->is_quoted;
		redirect->to.filename = filename;
		redirect->open_flags = O_RDONLY;
		return ;
	}
	if (r_kind == r_output_direction)
	{
		redirect->from.fd = STDOUT_FILENO;
		filename = xstrdup(token->next->word);
		redirect->is_filename_quoted = token->next->is_quoted;
		redirect->to.filename = filename;
		redirect->open_flags = O_CREAT | O_TRUNC | O_WRONLY;
		return ;
	}
	if (r_kind == r_appending_to)
	{
		redirect->from.fd = STDOUT_FILENO;
		filename = xstrdup(token->next->word);
		redirect->is_filename_quoted = token->next->is_quoted;
		redirect->to.filename = filename;
		redirect->open_flags = O_CREAT | O_APPEND | O_WRONLY;
		return ;
	}
	redirect->here_doc_eof = xstrdup(token->next->word);
	redirect->is_filename_quoted = token->next->is_quoted;
}

/*
トークンの種類からリダイレクト構造体を作る.
*/
t_redirect	*new_redirect(t_token *token)
{
	t_redirect	*result;

	result = xcalloc(1, sizeof(t_redirect));
	if (is_same_operator(token, "<<"))
	{
		fill_redirect(result, r_reading_until, token);
		return (result);
	}
	if (is_same_operator(token, ">>"))
	{
		fill_redirect(result, r_appending_to, token);
		return (result);
	}
	if (is_same_operator(token, "<"))
	{
		fill_redirect(result, r_input_direction, token);
		return (result);
	}
	fill_redirect(result, r_output_direction, token);
	return (result);
}

/*
append_token()と全く同じ処理だが、引数の型だけ異なる.
*/
void	append_redirect(t_redirect **head, t_redirect *element)
{
	t_redirect	*iter;

	if (*head == NULL)
	{
		*head = element;
		return ;
	}
	iter = *head;
	while (iter->next)
	{
		iter = iter->next;
	}
	iter->next = element;
}

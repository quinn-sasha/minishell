/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:59:11 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 14:38:36 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gather_heredoc(t_simple_command *command, t_map *envmap)
{
	t_redirect	*redirect;

	while (command != NULL)
	{
		redirect = command->redirect;
		while (redirect != NULL)
		{
			if (redirect->redirect_kind != r_reading_until)
			{
				redirect = redirect->next;
				continue ;
			}
			redirect->file_fd = read_heredoc(redirect->here_doc_eof,
					redirect->is_filename_quoted, envmap);
			if (redirect->file_fd == -1)
				return (FAILED);
			redirect = redirect->next;
		}
		command = command->next;
	}
	return (SUCCESS);
}

int	open_fd(t_redirect *redirect)
{
	char	*pathname;

	pathname = redirect->to.filename;
	return (open(pathname, redirect->open_flags, 0644));
}

int	open_redirect_file(t_simple_command *command)
{
	t_redirect	*current;

	current = command->redirect;
	while (current != NULL)
	{
		if (current->redirect_kind == r_reading_until)
		{
			current = current->next;
			continue ;
		}
		current->file_fd = open_fd(current);
		if (current->file_fd < 0)
		{
			perror_wrapper(current->to.filename, NULL, NULL);
			return (FAILED);
		}
		current = current->next;
	}
	return (SUCCESS);
}

void	do_redirect(t_redirect *redirect)
{
	if (redirect == NULL)
		return ;
	redirect->stash_fd = xdup(redirect->from.fd);
	xdup2(redirect->file_fd, redirect->from.fd);
	close(redirect->file_fd);
	do_redirect(redirect->next);
}

void	reset_redirect(t_redirect *redirect)
{
	if (redirect == NULL)
		return ;
	reset_redirect(redirect->next);
	if (redirect->stash_fd > 0)
	{
		xdup2(redirect->stash_fd, redirect->from.fd);
		close(redirect->stash_fd);
	}
}

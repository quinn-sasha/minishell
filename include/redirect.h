/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:07:36 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 08:07:37 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// read_until_delimiter
#define HEREDOC_INTERRUPTED 1
#define HEREDOC_FINISHED 0

// heredoc.c
int		stop_readline_if_sigint(void);
char	*expand_heredoc_line(char *line, t_map *envmap);
int		read_until_delimiter(int *pipefd, const char *delimiter, bool is_quoted,
			t_map *envmap);
int		read_heredoc(const char *delimiter, bool is_quoted, t_map *envmap);

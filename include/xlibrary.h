/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xlibrary.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:05:43 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 08:05:51 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XLIBRARY_H
# define XLIBRARY_H

void	*xmalloc(size_t size);
void	*xcalloc(size_t nmemb, size_t size);
char	*xstrdup(const char *s);
int		xdup(int oldfd);
int		xdup2(int oldfd, int newfd);
int		xpipe(int pipefd[2]);
int		xclose(int fd);

#endif

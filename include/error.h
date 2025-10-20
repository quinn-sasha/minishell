/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:05:09 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 08:07:03 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define PREFIX_ERROR "micro-shell: "
# define COMMAND_NOT_FOUND_STATUS 127
# define PERMISSION_DENIED_STATUS 126
# define ASSERT_ERROR_STATUS 255

# define COMMAND_NOT_FOUND_ERROR "command not found"
# define PERMISSION_DENIED_ERROR "permission denied"

void	prefix_error(void);
void	unclosed_quote_error(void);
void	syntax_error(const char *unexpected_token);
void	ambiguous_redirect_error(void);
void	fatal_error(const char *message);
void	perror_wrapper(const char *s1, const char *s2, const char *message);
void	assert_error(const char *message);
void	error_and_exit(const char *cmd, const char *message, int status);

#endif

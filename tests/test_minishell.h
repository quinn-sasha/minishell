/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minishell.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:10:49 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/02 20:11:50 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// test_builtin.c
int	test_is_builtin(void);

// test_parser_pipe.c
int	test_is_pipe(void);
int	test_count_pipes(void);

// test_parser_separator.c
int	test_is_separator(void);
int	test_count_tokens(void);

// test_utils.c
int	test_ft_strcmp(void);
int	test_ft_strlen(void);

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:12:12 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/02 20:11:24 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "test_minishell.h"

int	main(void)
{
	if (test_ft_strcmp() != 0 || test_ft_strlen() != 0
		|| test_is_pipe() != 0 || test_count_pipes() != 0
		|| test_is_separator() != 0 || test_count_tokens() != 0
		|| test_is_builtin() != 0)
		return (1);
	return (0);
}

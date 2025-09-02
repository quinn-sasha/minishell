/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:07:08 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/02 20:14:33 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief srcs/builtin.c内のis_builtinのテスト
 *
 * @author yurishik
 * @return すべてのケースでうまく行けば0、そうでなければ1
 */
int	test_is_builtin(void)
{
	int	passed;
	int	total;

	printf("==========test_is_builtin==========\n");
	passed = 0;
	total = 0;
	total++;
	if (is_builtin("pwd", "pwd"))
		passed++;
	else
		printf("[NG] 'pwd' vs 'pwd'\n");
	total++;
	if (is_builtin("   pwd  ", "pwd"))
		passed++;
	else
		printf("[NG] '   pwd  ' vs 'pwd'\n");
	total++;
	if (is_builtin("\tpwd\t", "pwd"))
		passed++;
	else
		printf("[NG] '\\tpwd\\t' vs 'pwd'\n");
	total++;
	if (!is_builtin("echo", "pwd"))
		passed++;
	else
		printf("[NG] 'echo' vs 'pwd'\n");
	total++;
	if (!is_builtin("pwda", "pwd"))
		passed++;
	else
		printf("[NG] 'pwda' vs 'pwd'\n");
	total++;
	if (!is_builtin(NULL, "pwd"))
		passed++;
	else
		printf("[NG] NULL vs 'pwd'\n");
	printf("Result: %d/%d tests passed\n", passed, total);
	if (passed == total)
		return (0);
	return (1);
}

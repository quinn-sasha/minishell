/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:47:41 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/02 17:26:34 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief srcs/parser.c内のis_pipeのテスト
 *
 * @author yurishik
 * @return すべてのケースでうまく行けば0、そうでなければ1
 */
int	test_is_pipe(void)
{
	int	passed;
	int	total;

	printf("==========test_is_pipe===========\n");
	passed = 0;
	total = 0;
	total++;
	if (is_pipe('|') == 1)
		passed++;
	else
		printf("[NG] '|' should return 1\n");
	total++;
	if (is_pipe('a') == 0)
		passed++;
	else
		printf("[NG] 'a' should return 0\n");
	total++;
	if (is_pipe(' ') == 0)
		passed++;
	else
		printf("[NG] ' ' should return 0\n");
	total++;
	if (is_pipe('\n') == 0)
		passed++;
	else
		printf("[NG] '\\n' should return 0\n");
	printf("Result: %d/%d tests passed\n", passed, total);
	if (passed == total)
		return (0);
	else
		return (1);
}

/**
 * @brief srcs/parser.c内のcount_pipesのテスト
 *
 * @author yurishik
 * @return すべてのケースでうまく行けば0、そうでなければ1
 */
int	test_count_pipes(void)
{
	int	passed;
	int	total;

	printf("==========test_count_pipes==========\n");
	passed = 0;
	total = 0;
	total++;
	if (count_pipes(NULL) == 0)
		passed++;
	else
		printf("[NG] NULL input\n");
	total++;
	if (count_pipes("") == 0)
		passed++;
	else
		printf("[NG] empty string\n");
	total++;
	if (count_pipes("echo 123") == 0)
		passed++;
	else
		printf("[NG] no pipe\n");
	total++;
	if (count_pipes("echo 1|grep 1|wc -l") == 2)
		passed++;
	else
		printf("[NG] two pipes\n");
	total++;
	if (count_pipes("|echo 1||wc -l|") == 4)
		passed++;
	else
		printf("[NG] four pipes with consecutive\n");
	printf("Result: %d/%d tests passed\n", passed, total);
	if (passed == total)
		return (0);
	return (1);
}

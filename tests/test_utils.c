/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:04:33 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/02 10:25:35 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief srcs/ft_utils.c内のft_strcmpのテストを書いてみる
 *
 * @author yurishik
 * @return すべてのケースでうまく行けば0、そうでなければ1
 */
int	test_ft_strcmp(void)
{
	int	passed;
	int	total;

	passed = 0;
	total = 0;
	total++;
	if (ft_strcmp("abc", "abc") == 0)
		passed++;
	else
		printf("[NG] 'abc' vs 'abc'\n");
	total++;
	if (ft_strcmp("abc", "abd") < 0)
		passed++;
	else
		printf("[NG] 'abc' vs 'abd'\n");
	total++;
	if (ft_strcmp("abd", "abc") > 0)
		passed++;
	else
		printf("[NG] 'abd' vs 'abc'\n");
	total++;
	if (ft_strcmp("", "") == 0)
		passed++;
	else
		printf("[NG] '' vs ''\n");
	total++;
	if (ft_strcmp("", "a") < 0)
		passed++;
	else
		printf("[NG] '' vs 'a'\n");
	total++;
	if (ft_strcmp("a", "") > 0)
		passed++;
	else
		printf("[NG] 'a' vs ''\n");
	total++;
	if (ft_strcmp(NULL, "abc") < 0)
		passed++;
	else
		printf("[NG] NULL vs 'abc'\n");
	total++;
	if (ft_strcmp("abc", NULL) > 0)
		passed++;
	else
		printf("[NG] 'abc' vs NULL\n");
	total++;
	if (ft_strcmp(NULL, NULL) == 0)
		passed++;
	else
		printf("[NG] NULL vs NULL\n");
	printf("\nResult: %d/%d tests passed\n", passed, total);
	if (passed == total)
		return (0);
	else
		return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:04:33 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/02 17:25:31 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief srcs/utils.c内のft_strcmpのテストを書いてみる
 *
 * @author yurishik
 * @return すべてのケースでうまく行けば0、そうでなければ1
 */
int	test_ft_strcmp(void)
{
	int	passed;
	int	total;

	printf("==========test_ft_strcmp==========\n");
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
	printf("Result: %d/%d tests passed\n", passed, total);
	if (passed == total)
		return (0);
	else
		return (1);
}

/**
 * @brief srcs/utils.c内のft_strlenのテスト
 *
 * @author yurishik
 * @return すべてのケースでうまく行けば0、そうでなければ1
 */
int	test_ft_strlen(void)
{
	const char	*test_cases[5];
	size_t		expected[5];
	size_t		result;
	size_t		i;
	int			status;

	printf("==========test_ft_strlen==========\n");
	test_cases[0] = "";
	test_cases[1] = "abcde";
	test_cases[2] = "Hello, world!";
	test_cases[3] = "1234567890";
	test_cases[4] = "\0hidden";
	expected[0] = 0;
	expected[1] = 5;
	expected[2] = 13;
	expected[3] = 10;
	expected[4] = 0;
	i = 0;
	status = 0;
	while (i < sizeof(test_cases) / sizeof(test_cases[0]))
	{
		result = ft_strlen(test_cases[i]);
		printf("Test %zu: \"%s\"\n", i + 1, test_cases[i]);
		printf("ft_strlen: %zu, expected: %zu -> ", result, expected[i]);
		if (result == expected[i])
			printf("PASS\n\n");
		else
			printf("FAIL\n\n");
		if (result != expected[i])
			status = 1;
		i++;
	}
	return (status);
}

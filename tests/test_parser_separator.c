/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser_separator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:47:41 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/02 17:26:34 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief srcs/parser_separator.c内のis_separatorのテスト
 *
 * @author yurishik
 * @return すべてのケースでうまく行けば0、そうでなければ1
 */
int	test_is_separator(void)
{
	int	passed;
	int	total;

	printf("==========test_is_separator===========\n");
	passed = 0;
	total = 0;

	/* スペースは区切り */
	total++;
	if (is_separator(' ') == 1)
		passed++;
	else
		printf("[NG] ' ' should return 1\n");

	/* タブは区切り */
	total++;
	if (is_separator('\t') == 1)
		passed++;
	else
		printf("[NG] '\\t' should return 1\n");

	/* 普通の文字は区切りではない */
	total++;
	if (is_separator('a') == 0)
		passed++;
	else
		printf("[NG] 'a' should return 0\n");

	/* 改行は区切りではない */
	total++;
	if (is_separator('\n') == 0)
		passed++;
	else
		printf("[NG] '\\n' should return 0\n");

	/* 記号は区切りではない */
	total++;
	if (is_separator('|') == 0)
		passed++;
	else
		printf("[NG] '|' should return 0\n");

	printf("Result: %d/%d tests passed\n", passed, total);
	if (passed == total)
		return (0);
	else
		return (1);
}

/**
 * @brief srcs/parser_separator.c内のcount_tokensのテスト
 *
 * @author yurishik
 * @return すべてのケースでうまく行けば0、そうでなければ1
 */
int	test_count_tokens(void)
{
	int	passed;
	int	total;

	printf("==========test_count_tokens===========\n");
	passed = 0;
	total = 0;
	total++;
	if (count_tokens("") == 0)
		passed++;
	else
		printf("[NG] \"\" should return 0\n");
	total++;
	if (count_tokens("hello") == 1)
		passed++;
	else
		printf("[NG] \"hello\" should return 1\n");
	total++;
	if (count_tokens("hello world") == 2)
		passed++;
	else
		printf("[NG] \"hello world\" should return 2\n");
	total++;
	if (count_tokens("   hello   ") == 1)
		passed++;
	else
		printf("[NG] \"   hello   \" should return 1\n");
	total++;
	if (count_tokens("a\tb\tc") == 3)
		passed++;
	else
		printf("[NG] \"a\\tb\\tc\" should return 3\n");
	total++;
	if (count_tokens("a \t b\t c") == 3)
		passed++;
	else
		printf("[NG] \"a \\t b\\t c\" should return 3\n");
	total++;
	if (count_tokens("a   b\t\tc") == 3)
		passed++;
	else
		printf("[NG] \"a   b\\t\\tc\" should return 3\n");
	printf("Result: %d/%d tests passed\n", passed, total);
	if (passed == total)
		return (0);
	else
		return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:57:37 by squinn            #+#    #+#             */
/*   Updated: 2025/09/28 17:29:30 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (s1 == s2)
		return (0);
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
		{
			return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
		}
		s1++;
		s2++;
	}
	return (0);
}

/*
#include <assert.h>
#include <stdio.h>
#include <string.h>

int	main(int argc, char *argv[]) {
	(void)argc;
  assert(strcmp(argv[1], argv[2]) == ft_strcmp(argv[1], argv[2]));
}
*/

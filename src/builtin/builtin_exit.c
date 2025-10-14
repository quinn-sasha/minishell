/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:51:24 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/14 15:56:20 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int	is_numeric(const char *str)
{
	const char	*current_ptr;
	int			has_digit;

	if (str == NULL || *str == '\0')
		return (FALSE);
	current_ptr = str;
	has_digit = FALSE;
	if (*current_ptr == '-' || *current_ptr == '+')
		current_ptr++;
	while (ft_isdigit(*current_ptr))
	{
		has_digit = TRUE;
		current_ptr++;
	}
	if (*current_ptr == '\0' && has_digit == TRUE)
		return (TRUE);
	return (FALSE);
}

unsigned long	set_minus_overflow_flg(const char **str,
		int *is_minus, int *is_overflow)
{
	unsigned long	long_num;
	unsigned long	long_max_prefix;
	unsigned long	long_max_digit;

	long_num = 0;
	*is_minus = FALSE;
	*is_overflow = FALSE;
	if (**str == '-')
		*is_minus = TRUE;
	if (**str == '-' || **str == '+')
		(*str)++;
	long_max_prefix = (unsigned long)LONG_MAX / 10;
	long_max_digit = (unsigned long)LONG_MAX % 10;
	while (ft_isdigit(**str))
	{
		if (long_num > long_max_prefix
			|| (long_num == long_max_prefix
				&& **str - '0' > (int)long_max_digit + *is_minus))
			*is_overflow = TRUE;
		if (*is_overflow == FALSE)
			long_num = long_num * 10 + (unsigned long)(*str - '0');
		(*str)++;
	}
	return (long_num);
}

long	string_to_long(char *str, char **ptr)
{
	unsigned long	long_num;
	int				is_minus;
	int				is_overflow;
	long			result;

	long_num = set_minus_overflow_flg((const char **)&str,
			&is_minus, &is_overflow);
	*ptr = (char *)str;
	if (is_overflow && is_minus)
		result = LONG_MIN;
	else if (is_overflow)
		result = LONG_MAX;
	if (is_overflow == TRUE)
	{
		errno = ERANGE;
		return (result);
	}
	if (is_minus == TRUE)
		return (-((long)long_num));
	else
		return ((long)long_num);
}

int	builtin_exit(char **argv, t_map *envmap)
{
	long	res;
	char	*arg;
	char	*ptr;

	if (argv[1] == NULL)
		exit(envmap->last_status);
	if (argv[2] != NULL)
	{
		perror_wrapper("exit", NULL, "too many arguments");
		exit(1);
	}
	arg = argv[1];
	if (is_numeric(arg))
	{
		errno = 0;
		res = string_to_long(arg, &ptr);
		if (errno == 0 && *ptr == '\0')
			exit((int)res);
	}
	perror_wrapper("exit", argv[1], "numeric argument required");
	exit(255);
}

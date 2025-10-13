/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:51:24 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/10 16:42:56 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int is_numeric(const char *str)
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


long	string_to_long(char *str, char **ptr)
{
	unsigned long	long_num;
	int				is_minus;
	int				is_overflow;
	
	long_num = 0;
	is_minus = FALSE;
	is_overflow = FALSE;
	if (*str == '-')
		is_minus = TRUE;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		if (long_num > (unsigned long)LONG_MAX / 10)
			is_overflow = TRUE;
		if (long_num == (unsigned long)LONG_MAX / 10 && (*str - '0') > (int)((unsigned long)LONG_MAX % 10 + is_minus))
			is_overflow = TRUE;
		if (is_overflow == TRUE)
		{
			errno = ERANGE;
			*ptr = (char *)str;
			return (FAILED);
		}
		long_num = long_num * 10 + (*str - '0');
		str++;
	}
	*ptr = (char *)str;
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

	if (argv[2] != NULL)
	{
		perror("exit");
		return (FAILED);
	}
	if (argv[1] == NULL)
		exit(envmap->last_status);
	arg = argv[1];
	if (is_numeric(arg))
	{
    	errno = 0;
    	res = string_to_long(arg, &ptr);
    	if (errno == 0 && *ptr == '\0')
        	exit((int)res);
	}
	perror("exit");
	exit(255);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:19:37 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 15:11:41 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*unsigned_itoa(unsigned long long num, unsigned int base)
{
	static char	buffer[MAX_ADDRESS_LENGTH + 1];
	static char	*symbols;
	char		*ptr;

	symbols = "0123456789abcdef";
	ptr = &buffer[MAX_ADDRESS_LENGTH];
	*ptr = '\0';
	if (num == 0)
	{
		ptr--;
		*ptr = '0';
		return (ptr);
	}
	while (num)
	{
		ptr--;
		*ptr = symbols[num % base];
		num /= base;
	}
	return (ptr);
}

size_t	count_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

void	free_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*join_str_separator(const char *s1, const char *s2, char sep)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)xcalloc(len1 + len2 + 2, sizeof(char));
	ft_memcpy(result, s1, len1);
	result[len1] = sep;
	ft_memcpy(result + len1 + 1, s2, len2);
	return (result);
}

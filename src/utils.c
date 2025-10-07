#include "minishell.h"

// 文字列を動的に割り当てていないことに注意
char	*unsigned_itoa(unsigned long long num, unsigned int base)
{
	static char	buffer[MAX_ADDRESS_LENGTH + 1];
	static char	*symbols = "0123456789abcdef";
	char		*ptr;

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

static int	is_in_set(char letter, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == letter)
			return (1);
		i++;
	}
	return (0);
}

int	count_words(char const *s, const char *set)
{
	int	result;
	int	i;

	if (s[0] == '\0')
		return (0);
	result = 0;
	i = 0;
	while (s[i])
	{
		if (is_in_set(s[i], set)) {
			i++;
			continue ;
		}
		while (s[i] && !is_in_set(s[i], set))
			i++;
		result++;
	}
	return (result);
}

void	free_array(char	**array)
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

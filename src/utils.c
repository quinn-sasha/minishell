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


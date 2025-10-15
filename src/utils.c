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

int count_words(char *s, const char *excluded_chars) {
  if (*s == '\0')
    return 0;
  int result = 0;
  while (*s) {
    if (is_in_set(*s, excluded_chars)) {
      s++;
      continue;
    }
    if (is_quote(*s)) {
      consume_quoted_word(&s, s);
      continue;
    }
    while (*s && !is_in_set(*s, excluded_chars))
      s++;
    result++;
  }
  return result;
}

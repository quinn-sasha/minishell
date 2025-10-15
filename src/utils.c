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

size_t	count_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
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

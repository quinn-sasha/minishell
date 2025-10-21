/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_consume.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:20:13 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 15:21:19 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*consume_operator(char **input_to_return, char *input)
{
	static const char	*operators[] = {"<<", ">>", "<", ">", "|", NULL};
	int					i;
	char				*word;
	t_token				*result;

	i = 0;
	while (operators[i])
	{
		if (ft_strncmp(input, operators[i], ft_strlen(operators[i])) != 0)
		{
			i++;
			continue ;
		}
		word = ft_strdup(operators[i]);
		result = new_token(TOKEN_OPERATOR, word);
		*input_to_return += ft_strlen(operators[i]);
		return (result);
	}
	return (NULL);
}

void	consume_quoted_word(char **input_to_return, char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = input[i];
	i++;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] == '\0')
		assert_error("Word is not quoted");
	i++;
	*input_to_return += i;
}

t_token	*consume_word(char **input_to_return, char *input)
{
	bool	is_quoted_flag;
	char	*c_ptr;
	char	*word;
	t_token	*result;

	is_quoted_flag = false;
	c_ptr = input;
	while (*c_ptr)
	{
		if (is_metacharacter(*c_ptr))
			break ;
		if (!is_quote(*c_ptr))
		{
			c_ptr++;
			continue ;
		}
		consume_quoted_word(&c_ptr, c_ptr);
		is_quoted_flag = true;
	}
	word = ft_substr(input, 0, c_ptr - input - 1);
	result = new_token(TOKEN_WORD, word);
	result->is_quoted = is_quoted_flag;
	*input_to_return = c_ptr;
	return (result);
}

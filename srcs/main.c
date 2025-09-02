/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:27:42 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/02 16:55:32 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 *
 * @author yurishik
 * @return 
 */
int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (input && *input)
		{
			if (ft_strcmp(input, "pwd") == 0)
				builtin_pwd();
			add_history(input);
		}
		free(input);
	}
	printf("exit\n");
	return (0);
}

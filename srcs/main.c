/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:27:42 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/02 20:03:47 by yurishik         ###   ########.fr       */
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
	char	**commands;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (input && *input)
		{
			if (is_builtin(input, "pwd"))
				builtin_pwd();
			if (is_builtin(input, "exit"))
				builtin_exit();
			if (split_by_pipe(input, &commands) == 0)
			{
				print_str_array(commands);
			}
			add_history(input);
		}
		free(input);
	}
	printf("exit\n");
	return (0);
}

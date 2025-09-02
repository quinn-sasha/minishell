/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:27:42 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/02 20:54:33 by yurishik         ###   ########.fr       */
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
	int		num_cmd;

	num_cmd = 0;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (input && *input)
		{
			if (check_builtin(input))
				continue ;
			if (split_by_pipe(input, &commands, &num_cmd) == 0)
			{
				printf("num_cmd: %d\n", num_cmd);
				print_str_array(commands);
			}
			add_history(input);
		}
		free(input);
	}
	printf("exit\n");
	return (0);
}

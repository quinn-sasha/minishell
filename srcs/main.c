/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:27:42 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/03 09:12:15 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 *
 * @author yurishik
 * @return 
 */
static void	process_command(char *cmd, char **envp)
{
	char	**tokens;

	if (split_by_separator(cmd, &tokens) != 0)
	{
		printf("error: cannot split by separator\n");
		return ;
	}
	execute_command(tokens, envp);
	free_str_array(tokens);
}

/**
 * @brief
 *
 * @author yurishik
 * @return 
 */
static void	process_input(char *input, char **envp)
{
	char	**commands;
	int		num_cmd;
	int		i;

	num_cmd = 0;
	if (*input == '\0')
		return ;
	if (check_builtin(input))
		return ;
	if (split_by_pipe(input, &commands, &num_cmd) != 0)
	{
		printf("error: cannot split by pipe\n");
		return ;
	}
	i = 0;
	while (i < num_cmd)
	{
		printf("command %d\n", i);
		process_command(commands[i], envp);
		i++;
	}
	free_str_array(commands);
	add_history(input);
}

/**
 * @brief
 *
 * @author yurishik
 * @return 
 */
int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		process_input(input, envp);
		free(input);
	}
	printf("exit\n");
	return (0);
}

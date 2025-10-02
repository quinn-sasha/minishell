/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:27:42 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/02 16:21:02 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

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
static void	process_input(char *input, t_env **env, char **envp)
{
	char	**commands;
	int		num_cmd;
	int		i;

	printf("%s\n", input);
	num_cmd = 0;
	if (*input == '\0')
		return ;
	if (check_builtin(env, input))
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
int	main(void)
{
	char	*input;
	t_env	*env;

	env = NULL;
	if (initialize_environ(&env, environ) != 0)
	{
		perror("initialize env");
		return (1);
	}
	printf("%s\n", find_env(env, "USER"));
	builtin_unset(&env, "USER");
	printf("%s\n", find_env(env, "USER"));
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		process_input(input, &env, environ);
		free(input);
	}
	printf("exit\n");
	env_lstfree(env);
	return (0);
}

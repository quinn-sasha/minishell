/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:19:44 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 20:19:02 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_number;

static int run_command(t_simple_command *command, t_map *envmap) {
	if (expand(command, envmap) == EXPAND_SYNTAX_ERROR) {
		clean_command(&command);
		return EXIT_FAILURE;
	}
	int last_status = exec(command, envmap);
	clean_command(&command);
	return last_status;
}

void	interpret(char *input, t_map *envmap)
{
	t_token				*token;
	t_simple_command	*command;

	token = tokenize(input);
	if (token == NULL)
	{
		envmap->last_status = SYNTAX_ERROR_LAST_STATUS;
		return ;
	}
	if (at_eof(token))
	{
		free_token_list(token);
		return ;
	}
	if (parse(&command, token) == PARSE_SYNTAX_ERROR)
	{
		envmap->last_status = SYNTAX_ERROR_LAST_STATUS;
		return ;
	}
	envmap->last_status = run_command(command, envmap);
}

int	main(void)
{
	t_map	*environment;
	char	*input;
	int		last_status;

	set_up_signal();
	environment = init_environment();
	while (TRUE)
	{
		input = readline("micro-shell> ");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		interpret(input, environment);
		free(input);
	}
	last_status = environment->last_status;
	clean_environment(environment);
	return (last_status);
}

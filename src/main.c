/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:19:44 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 09:19:44 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_number;

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
	command = NULL;
	if (parse(&command, token) == PARSE_SYNTAX_ERROR)
	{
		envmap->last_status = SYNTAX_ERROR_LAST_STATUS;
		return ;
	}
	if (expand(command, envmap) == EXPAND_SYNTAX_ERROR)
	{
		envmap->last_status = EXIT_FAILURE;
		clean_command(&command);
		return ;
	}
	envmap->last_status = exec(command, envmap);
	clean_command(&command);
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

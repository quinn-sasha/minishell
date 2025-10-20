/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:20:04 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 19:59:20 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal_number;

int	check_state(void)
{
	if (g_signal_number == 0)
	{
		return (SUCCESS);
	}
	if (g_signal_number == SIGINT)
	{
		g_signal_number = 0;
		rl_done = true;
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	return (SUCCESS);
}

void	set_up_signal(void)
{
	g_signal_number = 0;
	set_signal_handler(SIGINT);
	ignore_signal(SIGQUIT);
	rl_outstream = stderr;
	if (isatty(STDIN_FILENO))
	{
		rl_event_hook = check_state;
	}
}

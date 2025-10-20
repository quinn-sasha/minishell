/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:20:04 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 19:59:11 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal_number;

void	signal_handler(int signum)
{
	g_signal_number = signum;
}

void	set_signal_handler(int signum)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = signal_handler;
	if (sigaction(signum, &sa, NULL) == FAILED)
	{
		fatal_error("sigaction()");
	}
}

void	ignore_signal(int signum)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	if (sigaction(signum, &sa, NULL) == FAILED)
	{
		fatal_error("sigaction()");
	}
}

void	reset_signal(int signum)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_DFL;
	if (sigaction(signum, &sa, NULL) == FAILED)
	{
		fatal_error("sigaction()");
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:05:39 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 08:07:26 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

void	signal_handler(int signum);
void	set_signal_handler(int signum);
void	ignore_signal(int signum);
void	reset_signal(int signum);
int		check_state(void);
void	set_up_signal(void);

#endif

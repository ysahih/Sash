/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:27:22 by ysahih            #+#    #+#             */
/*   Updated: 2023/07/25 09:56:15 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_int(int sig)
{
	(void)sig;
	if (g_gl.rl)
		return ;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_handler(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, handle_int);
	signal(SIGQUIT, SIG_IGN);
}

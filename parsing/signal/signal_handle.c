/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:40:55 by shebaz            #+#    #+#             */
/*   Updated: 2024/12/07 12:04:33 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_ctrl_c(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_var->exit_status = 130;
}

void	handle_signal(void)
{
	signal(SIGINT, (__sighandler_t)handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:45:07 by shebaz            #+#    #+#             */
/*   Updated: 2024/11/24 18:40:03 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_numeric(const char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_exit(char **args)
{
	ft_putstr_fd("exit\n", 1);
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n", args[1]);
			g_var->exit_status = 2;
			exit(g_var->exit_status);
		}
		g_var->exit_status = atoll(args[1]);
	}
	if (g_var->exit_status < INT_MIN || g_var->exit_status > INT_MAX)
		ft_putstr_fd("exit: numeric argument required", 2);
	else if (args[1] && args[2])
		return (g_var->exit_status = 1,
			ft_putstr_fd("bash: exit: too many arguments\n", 2), 1);
	else if (args[1] && !is_numeric(args[1]))
		ft_putstr_fd("exit: numeric argument required\n", 2);
	if (!is_numeric(args[1]) || g_var->exit_status < INT_MIN
		|| g_var->exit_status > INT_MAX)
		g_var->exit_status = 2;
	exit(g_var->exit_status);
	return (0);
}

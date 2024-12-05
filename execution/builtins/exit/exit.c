/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:45:07 by shebaz            #+#    #+#             */
/*   Updated: 2024/12/05 20:06:50 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_digit(char c)
{
	if (c <= '0' || c >= '9')
		return (0);
	return (1);
}

int	is_numeric(const char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0')
	{
		printf("minishell: exit: %s: numeric argument required\n", str);
		return (0);
	}
	while (*str)
	{
		if (!is_digit(*str))
		{
			printf("minishell: exit: %s:numeric argument required\n", str);
			return (0);
		}
		str++;
	}
	g_var->exit_status = 2;
	exit(g_var->exit_status);
	return (1);
}

int	ft_exit(char **args)
{
	int	exit_status;

	exit_status = g_var->exit_status;
	ft_putstr_fd("exit\n", 1);
	if (!args[1])
		exit(g_var->exit_status);
	if (args[1])
	{
		is_numeric(args[1]);
		exit_status = atoll(args[1]);
	}
	if (exit_status < INT_MIN || exit_status > INT_MAX)
		ft_putstr_fd("exit: numeric argument required", 2);
	else if (args[1] && args[2])
		return (g_var->exit_status = 1,
			ft_putstr_fd("bash: exit: too many arguments\n", 2), 1);
	else if (args[1] && !is_numeric(args[1]))
		ft_putstr_fd("exit: numeric argument required\n", 2);
	else if (!is_numeric(args[1]) || exit_status < INT_MIN
		|| exit_status > INT_MAX)
		exit_status = 2;
	exit(exit_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeroual <szeroual@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-17 08:53:48 by szeroual          #+#    #+#             */
/*   Updated: 2024-11-17 08:53:48 by szeroual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../externel_folder/libftt/libft.h"
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

int	ft_exit(t_shell *shell)
{
	int	exit_status;

	exit_status = shell->exit_status;
	ft_putstr_fd("exit\n", 1);
	if (shell->args[1])
	{
		if (!is_numeric(shell->args[1]))
			return (1);
		exit_status = atoll(shell->args[1]);
	}
	else
	{
		exit_status = 0;
		return (0);
	}
	if (exit_status < INT_MIN || exit_status > INT_MAX)
		ft_putstr_fd("exit: numeric argument required", 2);
	else if (shell->args[1] && shell->args[2])
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		return (1);
	}
	else if (shell->args[1] && !is_numeric(shell->args[1]))
		ft_putstr_fd("exit: numeric argument required\n", 2);
	if (!is_numeric(shell->args[1]) || exit_status < INT_MIN
		|| exit_status > INT_MAX)
		exit_status = 2;
	exit(exit_status);
	return (0);
}


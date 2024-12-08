/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:12:31 by shebaz            #+#    #+#             */
/*   Updated: 2024/12/07 14:42:34 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_global	*g_var = NULL;

void	initialisation(char **envp)
{
	initiale_global(init_env(envp));
}

void	error_malloc(void)
{
	perror("malloc");
	exit(EXIT_FAILURE);
}

t_envi	*init_env(char **en)
{
	t_envi	*env_list;
	int		i;
	char	*env_entry;

	env_list = NULL;
	i = 0;
	while (en[i])
	{
		env_entry = ft_strdup(en[i]);
		if (!env_entry)
			error_strdup();
		process_env_entry(env_entry, &env_list);
		i++;
	}
	return (env_list);
}

int	main(int argc, char **argv, char **en)
{
	(void)argc;
	(void)argv;
	initialisation(en);
	shell_loop(g_var->envp);
	return (0);
}

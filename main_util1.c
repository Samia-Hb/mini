/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_util1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:29:05 by szeroual          #+#    #+#             */
/*   Updated: 2024/12/07 14:42:19 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_strdup(void)
{
	perror("strdup");
	exit(EXIT_FAILURE);
}

void	initiale_global(t_envi *env)
{
	g_var = ft_malloc(1, sizeof(struct s_global));
	if (!g_var)
	{
		perror("calloc failed");
		exit(EXIT_FAILURE);
	}
	g_var->envp = env;
	g_var->exit_status = 0;
	g_var->red_error = 0;
	g_var->flag = 0;
	g_var->pid_size = 0;
}

void	handle_input(char *input, t_envi *envp)
{
	t_token	**tokens;
	t_cmd	*cmd;

	if (!ft_strlen(input))
		return ;
	add_history(input);
	tokens = tokenize(input);
	if (check_syntax_errors(*tokens))
	{
		g_var->exit_status = 2;
		return ;
	}
	if (!expand(*tokens))
		return ;
	cmd = analyse_tokens(tokens);
	if (g_var->flag == 7)
		return ;
	execute_arguments(cmd, envp);
}

void	shell_loop(t_envi *envp)
{
	char	*input;

	while (1)
	{
		handle_signal();
		g_var->flag = 0;
		input = readline("minishell > ");
		if (!input)
		{
			printf("exit\n");
			rl_clear_history();
			// clean_gc();
			break ;
		}
		handle_input(input, envp);
	}
	// ft_free_envp(envp);
}
//3271 in 142block
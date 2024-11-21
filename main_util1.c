/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_util1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:29:05 by szeroual          #+#    #+#             */
/*   Updated: 2024/11/22 00:50:22 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_box(t_mini *box, char **envp)
{
	box->env = init_env(envp);
	box->shell = init_shell();
	box->ptr = NULL;
	box->arr = NULL;
	box->last_exit_status = 0;
}

void	error_strdup(void)
{
	perror("strdup");
	exit(EXIT_FAILURE);
}

void	initialisation(t_mini *box, char **envp)
{
	initiale_global(init_env(envp));
	init_box(box, envp);
}

void	handle_input(char *input, t_mini *box)
{
	t_token	**tokens;
	t_cmd	*cmd;

	if (!ft_strlen(input))
		return ;
	add_history(input);
	tokens = tokenize(input);
	if (check_syntax_errors(*tokens))
		return ;
	if (!expand(*tokens))
		return ;
	cmd = analyse_tokens(tokens);
	// print_cmd(cmd);
	// exit(1);
	execute_arguments(cmd, box);
}

void	shell_loop(t_mini *box)
{
	char	*input;

	while (1)
	{
		handle_signal();
		input = readline("minishell > ");
		if (!input)
			break ;
		handle_input(input, box);
		free(input);
	}
}
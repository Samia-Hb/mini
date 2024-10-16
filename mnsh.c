#include "minishell.h"


void ft_clean(Token **tokens, t_parser *parsed, t_queue *queue)
{
	int i;

	i = 0;
	if(tokens)
	{
		while(*tokens)
		{
			free(tokens[i]->value);
			i++;
			(*tokens) = (*tokens)->next;
		}
		free(tokens);
	}
	if (parsed)
		free(parsed);
	if (queue)
		free(queue);
}
int	main()
{
    char	    *input;
    Token	    **tokens;
    t_queue     *queue;
    t_ast       *ast;
	int			errno;
    t_parser    *parsed;

	tokens = NULL;
	while (1)
	{
		handle_signal();
		input = readline("Minishell$ ");
		if (!input)
			break ;
        if (!strlen(input))
            main();
        add_history(input);
		tokens = tokenize(input);
		errno = check_syntax_errors(*tokens);
        if (errno)
            main();
        expand(*tokens);
		parsed = analyse_tokens(tokens);
		queue = generate_postfix(parsed);
		ast = generate_ast_from_postfix(queue);
		// printf("======>%s\n",ast->data->arguments[0]);
		// printf("======>%s\n",ast->data->arguments[1]);
		// printf("======>%s\n",ast->data->arguments[2]);
		// rl_clear_history();
		// exit(1);
	}
	return (0);
}



		// Token *token = *tokens;
		// int i ;
		// while (token)
		// {
		// 	i = 0;
		// 	printf("token = %s\n", token->value);
		// 	if (token->expanded_value)
		// 	{
		// 		while (token->expanded_value[i])
		// 		{
		// 			printf("expanded_arg[%d] = %s\n",i, token->expanded_value[i]);
		// 			i++;
		// 		}
		// 	}
		// 	token = token->next;
		// }
		// exit(1);





		// printf("======== Analysed result =======\n");
		// while (parsed)
		// {
		// 	i = 0;
		// 	printf ("token = %s\n", parsed->token->value);
		// 	if(parsed->arguments)
		// 	{
		// 		while (parsed->arguments[i])
		// 		{
		// 			printf("       arg[%d] = %s\n",i, parsed->arguments[i]);
		// 			i++;
		// 		}
		// 	}
		// 	parsed = parsed->next;
		// }
		// main();

		/// ///////////////////////////////////
		// int i;
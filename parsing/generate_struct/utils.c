/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:07:59 by shebaz            #+#    #+#             */
/*   Updated: 2024/11/01 13:04:29 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	push_back(t_cmd **lst, t_cmd *node)
{
	t_cmd	*tmp;

	node->next = NULL;
	if (!*lst)
		*lst = node;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

int	is_red(Token *token)
{
	if (token->type == TOKEN_REDIR_APPEND || token->type == TOKEN_REDIR_IN
		|| token->type == TOKEN_REDIR_OUT || token->type == TOKEN_REDIR_HERE_DOC)
		return (1);
	return (0);
}

int	nbr_argument(Token *tokens)
{
	int	nbr;
	int	i;
	int j;

	nbr = 0;
	j = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		i = 0;
		if (!is_operator(tokens))
		{
			while (tokens->expanded_value[i])
			{
				i++;
				nbr++;
			}
			tokens = tokens->next;
		}
		if (tokens && is_red(tokens))
		{
			tokens = tokens->next;
			tokens = tokens->next;
			while(nbr && j < 2)
			{
				nbr--;
				i++;
			}
		}
	}
	// printf("nbr = %d \n", nbr);
	return (nbr);
}

void	push_t_file(t_file **head, t_file *node)
{
	t_file	*tmp;

	node->next = NULL;
	if (!*head)
		*head = node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

int	get_red_type(Token *token)
{
	if (token->type == TOKEN_REDIR_IN)
		return (RE_IN);
	else if (token->type == TOKEN_REDIR_OUT)
		return (RE_OUT);
	else if (token->type == TOKEN_REDIR_APPEND)
		return (RE_APPEND);
	return (UNKOWN);
}

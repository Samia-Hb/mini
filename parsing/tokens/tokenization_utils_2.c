/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:37:34 by shebaz            #+#    #+#             */
/*   Updated: 2024/10/23 20:39:22 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

Token	*create_token(TokenType type, const char *value)
{
	Token	*token;

	token = malloc(sizeof(Token));
	if (!token)
	{
		printf("Error: Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

void	add_token(Token **tokens, TokenType type, const char *value, int *k)
{
	Token	*new_node;
	Token	*ptr;

	ptr = *tokens;
	new_node = create_token(type, value);
	if (!(*tokens))
		*tokens = new_node;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		new_node->previous = ptr;
		ptr->next = new_node;
	}
	(*k) = (*k) + ft_strlen(value);
}

int	ft_is_separator(char c)
{
	if (c == '>' || c == '<' || c == '\n' || c == '\t' || c == '|' || c == ' '
		|| c == '\t')
		return (1);
	return (0);
}

char	*handle_parentheses(char *str, char c)
{
	int		i;
	int		j;
	char	*word;

	i = 1;
	j = 0;
	while (str[i] && !isspace(str[i]))
	{
		if (str[i] == '\\' && str[i + 1] == c)
			i += 2;
		else
			i++;
		j++;
	}
	word = malloc(j + 1);
	if (!word)
	{
		fprintf(stderr, "Error: memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	word[0] = c;
	strncpy(word + 1, str + 1, j);
	word[j] = '\0';
	return (word);
}

char	*handle_quote(char *str)
{
	int		i;
	char	c;
	int		j;
	char	*word;

	i = 0;
	j = 0;
	word = malloc(ft_strlen(str) + 1);
	c = str[i];
	while (str[i] && !ft_is_separator(str[i]))
	{
		if (str[i] == c)
		{
			word[j++] = str[i++];
			while (str[i] && str[i] != c)
				word[j++] = str[i++];
			if (str[i] == c)
				word[j++] = str[i++];
		}
		else
			word[j++] = str[i++];
	}
	word[j] = '\0';
	return (word);
}

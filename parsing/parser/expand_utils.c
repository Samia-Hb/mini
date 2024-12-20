/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:19:37 by shebaz            #+#    #+#             */
/*   Updated: 2024/12/16 22:49:59 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_word_to_expand(char *str, int *j, char **result)
{
	char	*word;
	int		i;
	int		k;
	int		length;

	i = 0;
	while (str[*j] == '$')
		(*j)++;
	k = *j;
	if (is_number(str[*j]))
		return ((*j)++, ft_strdup(""));
	while (str[*j] && !is_special(str[*j]))
		(*j)++;
	length = (*j) - k;
	word = ft_malloc(length + 1, sizeof(char));
	if (!word)
		return (NULL);
	while (i < length)
		word[i++] = str[k++];
	word[i] = '\0';
	if (!word)
		word = ft_strdup("");
	case_function(str, result, j);
	return (word);
}

char	*get_word(char **string, int *counter)
{
	char	*result;
	int		i;

	i = 0;
	if ((*counter) > 1)
	{
		while ((*string)[i] && ((*string)[i] == ' ' || (*string)[i] == '\t'))
			i++;
		while ((*string)[i] && ((*string)[i] != ' ' && (*string)[i] != '\t'))
			i++;
		result = ft_strndup(*string, i);
		(*string) += i;
	}
	else
		result = ft_strndup((*string), ft_strlen(*string));
	(*counter)--;
	return (result);
}

char	*get_output(char *input)
{
	char	*str;
	int		i;
	int		k;

	k = 0;
	i = 0;
	str = NULL;
	while (input[i] == ' ' || input[i] == '\t')
	{
		i++;
		k++;
	}
	i = k;
	while (input[i] && !ft_is_separator(input[i]))
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			str = handle_quote(input + i);
			i += ft_strlen(str) - 1;
		}
		i++;
	}
	return (ft_strndup(input + k, i - k));
}

char	*get_string(char *input, int *i)
{
	char	*word;

	while (input[*i] == ' ' || input[*i] == '\t')
		(*i)++;
	if (input[*i] == '"' || input[*i] == '\'')
	{
		word = handle_quote(input + (*i));
		*i += ft_strlen(word);
	}
	else
	{
		word = get_output(input + (*i));
		*i += ft_strlen(word);
	}
	return (word);
}

void	add_quote(char *input, char **expanded_value, int *j)
{
	int		i;
	char	*result;

	i = 0;
	result = char_to_string(input[i], 0);
	*expanded_value = ft_strjoin(*expanded_value, result);
	(*j)++;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:05:46 by shebaz            #+#    #+#             */
/*   Updated: 2024/11/22 00:34:46 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	heredoc_process(t_cmd **node, t_file **head, t_token **tokens)
{
	int		fd;
	char	*processed_del;
	char	*line;
	int		pid;
	int		status;

	// printf("check here\n");
	(*tokens) = (*tokens)->next;
	processed_del = process_delimiter((*tokens)->value);
	printf("filname== %s\n", (*tokens)->value);
	fd = open((*tokens)->value, O_CREAT | O_TRUNC | O_RDWR, 0777);
	pid = fork();
	if (!pid)
	{
		// handle_signal();		
		while (1)
		{
			line = readline("heredoc > ");
			if (!line)
				break ;
			if (!ft_strcmp(line, processed_del))
				break ;
			if (!is_quoted((*tokens)->value))
				line = parse_line(line);
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		if (!line)
		{
			printf("checkkkkkkkkkkkk\n");
			unlink((*tokens)->value);
			printf("minishell : warning: here-document must delimited by end-of-file (wanted `%s')\n",(*tokens)->value);
			exit (130);
		}
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 130)
	{
		g_var->exit_status = 130;
		exit(g_var->exit_status);
	}
	(*node)->file = ft_malloc(sizeof(t_file), 1);
	(*node)->file->type = RE_HEREDOC;
	(*node)->file->filename = ft_strdup((*tokens)->value);
	push_t_file(head, (*node)->file);
	(*tokens) = (*tokens)->next;
}

void	red_process(t_token **tokens, t_cmd **node, int *i)
{
	t_file	*head;

	head = ft_malloc(sizeof(t_file), 1);
	head = NULL;
	while ((*tokens) && (*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->type == TOKEN_REDIR_HERE_DOC)
			heredoc_process(node, &head, tokens);
		if ((*tokens) && is_red(*tokens)
			&& (*tokens)->type != TOKEN_REDIR_HERE_DOC)
			fill_up_node(node, tokens, &head);
		while ((*tokens) && !is_red(*tokens) && (*tokens)->type != TOKEN_PIPE)
		{
			(*node)->arguments[(*i)++] = ft_strdup((*tokens)->value);
			(*tokens) = (*tokens)->next;
		}
	}
	(*node)->file = head;
}

char	*process_delimiter(char *tmp)
{
	int		i;
	int		j;
	char	*result;
	char	*hp;

	i = 0;
	result = ft_strdup("");
	while (tmp[i])
	{
		if (tmp[i] == '$' && tmp[i + 1]
			&& (tmp[i + 1] == '"' || tmp[i + 1] == '\''))
			i++;
		j = i;
		if (tmp[i] == '"' || tmp[i] == '\'')
			hp = get_inside_quote(tmp, &i, &j);
		else
		{
			while (tmp[i] && tmp[i] != '"' && tmp[i] != '\'')
				i++;
			hp = ft_strndup(tmp + j, i - j);
		}
		result = ft_strjoin(result, hp);
	}
	return (result);
}

void	create_node_arguments(t_cmd **node, t_token **tokens)
{
	int	i;
	int	j;

	i = 0;
	(*node)->arguments = ft_malloc(sizeof(char *), nbr_argument(*tokens) + 1);
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		j = 0;
		if (*tokens && !is_red(*tokens))
		{
			while ((*tokens)->expanded_value[j])
				(*node)->arguments[i++]
					= ft_strdup((*tokens)->expanded_value[j++]);
			(*tokens) = (*tokens)->next;
		}
		else
			red_process(tokens, node, &i);
	}
	go_to_next(tokens);
	(*node)->arguments[i] = NULL;
}

t_cmd	*analyse_tokens(t_token **tokens)
{
	t_cmd	*head;
	t_cmd	*node;

	head = NULL;
	while (*tokens)
	{
		node = ft_malloc(sizeof(t_cmd), 1);
		node->arguments = NULL;
		node->file = NULL;
		if ((*tokens)->type == TOKEN_COMMAND
			|| (*tokens)->type == TOKEN_BUILT_IN)
			create_node_arguments(&node, tokens);
		else if ((*tokens)->type != TOKEN_COMMAND
			|| (*tokens)->type != TOKEN_BUILT_IN)
			create_node_arguments(&node, tokens);
		else
			(*tokens) = (*tokens)->next;
		push_back(&head, node);
	}
	return (head);
}

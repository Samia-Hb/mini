/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_util2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:30:12 by szeroual          #+#    #+#             */
/*   Updated: 2024/12/18 09:29:21 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envi	*create__node(char *name, char *value)
{
	t_envi	*new_node;

	new_node = malloc(1 * sizeof(t_envi));
	if (!new_node)
	{
		perror("calloc");
		exit(EXIT_FAILURE);
	}
	new_node->name = ft_strdup_1(name);
	new_node->vale = ft_strdup_1(value);
	if (!new_node->name || !new_node->vale)
	{
		perror("strdup");
		free(new_node->name);
		free(new_node->vale);
		free(new_node);
		exit(EXIT_FAILURE);
	}
	new_node->next = NULL;
	new_node->prv = NULL;
	return (new_node);
}

void	add_env_node(t_envi **env_list, t_envi *new_node)
{
	if (*env_list)
		(*env_list)->prv = new_node;
	new_node->next = *env_list;
	*env_list = new_node;
}

void	process_env_entry(char *env_entry, t_envi **env_list)
{
	char	*name;
	char	*value;
	t_envi	*new_node;

	name = strtok(env_entry, "=");
	value = strtok(NULL, "=");
	if (!name || !value)
	{
		perror("error");
		free(env_entry);
		return ;
	}
	new_node = create__node(name, value);
	add_env_node(env_list, new_node);
	free(env_entry);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:39:34 by shebaz            #+#    #+#             */
/*   Updated: 2024/12/07 14:26:52 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_node(void *data)
{
	t_gc	*node;

	node = malloc(1 * sizeof(t_gc));
	if (!node)
		return ;
	node->ptr = data;
	node->next = NULL;
	if (!g_var)
	{
		if (!g_var)
		{
			free(node);
			return ;
		}
		g_var->head = node;
	}
	else
	{
		node->next = g_var->head;
		g_var->head = node;
	}
}

void	*ft_malloc(int ele_nbr, size_t size)
{
	void	*ptr;

	ptr = malloc(ele_nbr * size);
	if (ptr != NULL)
		ft_memset(ptr, 0, ele_nbr * size);
	add_node(ptr);
	return (ptr);
}

void	ft_free_envp(t_envi *envp)
{
	t_envi	*current;
	t_envi	*next;

	current = envp;
	while (current)
	{
		next = current->next;
		if (current->name)
		{
			free(current->name);
			current->name = NULL;
		}
		if (current->vale)
		{
			free(current->vale);
			current->vale = NULL;
		}
		free(current);
		current = next;
	}
}

void	clean_gc(void)
{
	t_gc	*current;
	t_gc	*next;

	if (!g_var)
		return ;
	if (g_var->en)
		ft_free_array(g_var->en);
	current = g_var->head;
	if(current)
	{		
		while (current)
		{
			next = current->next;
			if (current->ptr)
				free(current->ptr);
			free(current);
			current = next;
		}
	}
	free(g_var);
	g_var = NULL;
}

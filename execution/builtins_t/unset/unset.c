/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:02:59 by shebaz            #+#    #+#             */
/*   Updated: 2024/11/25 18:52:50 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	clear_memory(t_envi *curr)
{
	free(curr->name);
	free(curr->vale);
	free(curr);
}

void	ft_remove(char **ptr, t_mini *box, int i)
{
	t_envi	*curr;
	t_envi	*prev;
	char	**av;

	av = ptr;
	while (av[i])
	{
		curr = box->env;
		prev = NULL;
		while (curr)
		{
			if (!ft_strcmp(curr->name, av[i]))
			{
				if (prev)
					prev->next = curr->next;
				else
					box->env = curr->next;
				clear_memory(curr);
				break ;
			}
			prev = curr;
			curr = curr->next;
		}
		i++;
	}
	curr = box->env;
	g_var->envp = box->env;
}

int	ft_unset(char **ptr, t_mini *box)
{
	int	j;
	int	i;

	j = 1;
	i = 1;
	if (!ptr || !ptr[1] || !box || !box->env)
		return (0);
	while (ptr[i])
	{
		if (ptr[1])
			ft_remove(ptr, box, j);
		else
			printf("unset: '%s': not a valid identifier\n", ptr[i]);
		i++;
	}
	// print_envi(box->env);
	return (0);
}

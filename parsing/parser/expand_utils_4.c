/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:25:26 by shebaz            #+#    #+#             */
/*   Updated: 2024/12/07 11:25:41 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*tidle_expansion(int *i)
{
	char	*result;

	result = getenv("HOME");
	if (!result)
		return (ft_strdup(""));
	*i += 1;
	return (ft_strdup(result));
}

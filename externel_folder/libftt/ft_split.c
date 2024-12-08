/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:09:51 by szeroual          #+#    #+#             */
/*   Updated: 2024/12/07 13:45:27 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	separate_string(char const *s, char c)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			wc++;
		i++;
	}
	return (wc);
}

static void	str_cpy(char *d, const char *src, char c)
{
	int	i;

	i = 0;
	while (src[i] != c && src[i])
	{
		d[i] = src[i];
		i++;
	}
	d[i] = '\0';
}

static int	allocate_substr(char **ar, const char *str, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			j = 0;
			while (str[i + j] != c && str[i + j])
				j++;
			ar[k] = ft_malloc(j + 1, sizeof(char));
			str_cpy(ar[k], str + i, c);
			i += j;
			k++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**ar;
	int		wc;

	if (!s)
		return (NULL);
	wc = separate_string(s, c);
	ar = ft_malloc((wc + 1), sizeof(char *));
	if (!ar)
		return (NULL);
	if (allocate_substr(ar, s, c) == 0)
		return (NULL);
	ar[wc] = 0;
	return (ar);
}

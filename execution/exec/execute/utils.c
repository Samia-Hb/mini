/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:07:11 by szeroual          #+#    #+#             */
/*   Updated: 2024/11/21 15:49:25 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	append_heredoc_prep(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->file->filename, O_RDWR, 0777);
	dup2(fd, STDIN_FILENO);
	g_var->in_fd = fd;
}

void	validate_cmd(t_cmd *cmd)
{
	if (ft_strchr(cmd->arguments[0], '/'))
		check_cmd_path(cmd);
	else
		check_command_name(cmd);
}

int	count_commands(t_cmd *cmd)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = cmd;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	*allocate_folders(char *path, int i)
{
	char	*folders;

	folders = malloc(i + 2);
	if (!folders)
	{
		perror("malloc failed");
		exit(1);
	}
	my_strncpy(folders, path, i + 1);
	return (folders);
}

void	my_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
}

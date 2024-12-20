/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeroual <szeroual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:19:58 by szeroual          #+#    #+#             */
/*   Updated: 2024/12/18 10:20:03 by szeroual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	in_file_prep(char *path, int is_builtin)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		g_var->exit_status = 1;
		perror(ft_strjoin("minishell: ", path));
		if (!is_builtin || g_var->size > 1)
		{
			close_open_file();
			exit(1);
		}
	}
	else
	{
		if (dup2(fd, 0) == -1)
		{
			perror("dup2");
			exit(1);
		}
		if (fd > 2)
			close(fd);
	}
}

void	out_file_prep(char *path, int is_builtin)
{
	int	fd;

	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
	{
		g_var->exit_status = 1;
		perror(ft_strjoin("minishell: ", path));
		if (!is_builtin || g_var->size > 1)
		{
			close_open_file();
			exit(1);
		}
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
		if (fd > 2)
			close(fd);
	}
}

void	append_file_prep(char *path, int is_builtin)
{
	int	fd;

	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		g_var->exit_status = 1;
		perror(ft_strjoin("minishell: ", path));
		if (!is_builtin || g_var->size > 1)
		{
			close_open_file();
			exit(1);
		}
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			exit(1);
		}
		if (fd > 2)
			close(fd);
	}
}

void	append_heredoc_prep(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0777);
	if (fd == -1)
	{
		close_open_file();
		exit(g_var->exit_status);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(filename);
}

void	files_redirections(t_cmd *cmd, int builtin)
{
	t_file	*curr_red;

	g_var->size = count_commands(cmd);
	curr_red = cmd->file;
	while (curr_red)
	{
		if (file_expansion_null(&curr_red->filename))
			curr_red = curr_red->next;
		else
		{
			if (curr_red->type == 1)
				out_file_prep(curr_red->filename, builtin);
			else if (curr_red->type == 2)
				in_file_prep(curr_red->filename, builtin);
			else if (curr_red->type == 3)
				append_heredoc_prep(curr_red->filename);
			else if (curr_red->type == 4)
				append_file_prep(curr_red->filename, builtin);
			curr_red = curr_red->next;
		}
	}
}

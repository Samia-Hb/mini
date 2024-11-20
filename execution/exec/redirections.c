/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:07:36 by szeroual          #+#    #+#             */
/*   Updated: 2024/11/20 22:01:04 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	in_file_prep(char *path, int is_builtin)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		g_var->exit_status = errno;
		g_var->red_error = 1;
		ft_putstr_fd("minishell: ", 2);
		perror(path);
		if (!is_builtin || g_var->size > 1)
			exit(1);
	}
	else
	{
		g_var->in_fd = 1;
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
		g_var->exit_status = errno;
		g_var->red_error = 1;
		ft_putstr_fd("minishell: ", 2);
		perror(path);
		if (!is_builtin || g_var->size > 1)
			exit(1);
	}
	else
	{
		if (!is_builtin || g_var->size > 1)
		{
			dup2(fd, 1);
			if (fd > 2)
				close(fd);
		}
		else
			g_var->out_fd = fd;
	}
}

void append_file_prep(char *path) 
{
    int fd; 
	
	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0777);
    if (fd == -1) 
    {
        perror(path);
        exit(1);
    } 
    else 
    {
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}

void handle_file_redirections(t_cmd *cmd,int btn) 
{
    files_redirections(cmd, btn != -1);
    if (btn == -1)
        validate_cmd(cmd);
    else if (g_var->pre_pipe_infd != -1 && !cmd->file->type)
        dup2(g_var->pre_pipe_infd, STDIN_FILENO);
}

void append_heredoc_prep(t_cmd *cmd)
{
	int fd;
	
	fd = open(cmd->file->filename, O_RDWR, 0777);
	dup2(fd, STDIN_FILENO);
	g_var->in_fd = fd;
}
void files_redirections(t_cmd *cmd, int builtin)
{
    g_var->size = count_commands(cmd);
    t_file *curr_red;
	
	curr_red = cmd->file;
    while (curr_red) 
    {
        // if (check_file_errors(curr_red->filename, builtin))
        //     return;
        if (curr_red->type == 1)
            out_file_prep(curr_red->filename, builtin);
        else if (curr_red->type == 2)
            in_file_prep(curr_red->filename , builtin);
	    else if (curr_red->type == 3)
		{
            append_heredoc_prep(cmd);		
			unlink(cmd->file->filename);
		}
        else if (curr_red->type == 4)
            append_file_prep(curr_red->filename);
        curr_red = curr_red->next;
    }
}

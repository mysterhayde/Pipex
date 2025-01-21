/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:39 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/21 13:49:11 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void parent_patern(t_path *path, int pipe_fd[2])
{
	int status;

	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		show_error(path, "Dup2 parent failed");
	if (dup2(path->fd_2, STDOUT_FILENO) == -1)
		show_error(path, "Dup2 parent failed");
	close(pipe_fd[0]);
	waitpid(-1, &status, 0);
	if (execve(path->binary[path->bin + 1], path->cmd[path->bin + 1], NULL) == -1)
		show_error(path, "Execve parent failed");
	return ;
}

static void	child_patern(t_path *path, int pipe_fd[2])
{
	close(pipe_fd[0]);
	if (dup2(path->fd_1, STDIN_FILENO) == -1)
		show_error(path, "dup2 child failed");
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		show_error(path, "dup2 child failed");
	close(pipe_fd[1]);
	if (execve(path->binary[path->bin], path->cmd[path->bin], NULL) == -1)
		show_error (path, "Execve child failed");
	return ;
}

void	pipex(t_path *path)
{
	int		pipe_fd[2];
	pid_t	pid;
	
	if (pipe(pipe_fd) == -1)
		show_error(path, "Pipe failed");
	pid = fork();
	if (pid == -1)
		show_error(path, "Fork failed");
	if (pid == 0)
		child_patern(path, pipe_fd);
	else
		parent_patern(path, pipe_fd);
	return ;
}

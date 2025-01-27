/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:39 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/27 14:19:13 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_patern_2(t_path *path, int pipe_fd[2])
{
	int	bin;

	bin = path->bin + 1;
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		show_error(path, "Dup2 parent failed");
	if (dup2(path->fd_2, STDOUT_FILENO) == -1)
		show_error(path, "Dup2 parent failed");
	close(pipe_fd[0]);
	if (execve(path->binary[bin], path->cmd[bin], NULL) == -1)
		show_error(path, "Execve parent failed");
	return ;
}

static void	child_patern_1(t_path *path, int pipe_fd[2])
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
	pid_t	pid_1;
	pid_t	pid_2;

	if (pipe(pipe_fd) == -1)
		show_error(path, "Pipe failed");
	pid_1 = fork();
	if (pid_1 == -1)
		show_error(path, "Fork failed");
	if (pid_1 == 0)
		child_patern_1(path, pipe_fd);
	pid_2 = fork();
	if (pid_2 == -1)
		show_error(path, "Fork failed");
	if (pid_2 == 0)
		child_patern_2(path, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (waitpid(pid_1, NULL, 0) == -1)
		show_error(path, "Waitpid failed");
	if (waitpid(pid_2, NULL, 0) == -1)
		show_error(path, "Waitpid failed");
	return ;
}

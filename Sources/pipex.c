/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:39 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/20 15:32:35 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	parent_patern(t_path *path, int pipe_fd[2], int fd, char str[11])
{
	close(pipe_fd[1]);
	if (read(pipe_fd[0], str, 10) == -1)
		show_error("Read failed");
	close(pipe_fd[0]);
	return ;
}

static void	child_patern(t_path *path, int pipe_fd[2])
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	if (execve(path->binary[0], path->cmd[0], NULL) == -1)
		show_error ("Execve failed");
	close(pipe_fd[1]);
	return ;
}

void	pipex(t_path *path)
{
	int		fd_r;
	int		fd_w;
	char	str[11];
	int		pipe_fd[2];
	pid_t	pid;

	fd_w = open("output.txt", O_WRONLY);
	if (fd_w == -1)
		show_error("Open fd_w failed");
	fd_r = open("input.txt", O_RDONLY);
	if (fd_r == -1)
		show_error("Open fd_r failed");
	if (pipe(pipe_fd) == -1)
		show_error("Pipe failed");
	dup2(fd_r, STDIN_FILENO);
	pid = fork();
	if (pid == -1)
		show_error("Fork failed");
	if (pid == 0)
		child_patern(path, pipe_fd);
	else
		parent_patern(path, pipe_fd, fd_w, str);
	if (write(fd_w, str, 4) == -1)
		show_error("write failed");
	return ;
}

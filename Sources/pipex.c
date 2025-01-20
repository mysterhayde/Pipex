/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:39 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/20 19:36:28 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void parent_patern(t_path *path, int pipe_fd[2], char str[11])
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], path->fd_2);
	if (execve(path->binary[path->bin], path->cmd[path->bin], NULL) == -1)
		show_error("Execve failed");
	path->bin++;
	close(pipe_fd[0]);
	return ;
}

static void	child_patern(t_path *path, int pipe_fd[2])
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	if (execve(path->binary[path->bin], path->cmd[path->bin], NULL) == -1)
		show_error ("Execve failed");
	path->bin++;
	close(pipe_fd[1]);
	return ;
}

void	pipex(t_path *path)
{
	char	str[11];
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		show_error("Pipe failed");
	pid = fork();
	if (pid == -1)
		show_error("Fork failed");
	if (pid == 0)
		child_patern(path, pipe_fd);
	else
		parent_patern(path, pipe_fd, str);
	return ;
}

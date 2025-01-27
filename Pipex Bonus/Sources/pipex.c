/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:12:23 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/27 16:46:57 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	children_patern(t_path *path, int *pipefd)
{
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		show_error(path, "Dup2 failed");
	if (dup2(path->fd_1, STDIN_FILENO) == -1)
		show_error(path, "Dup2 failed");
	close(pipefd[1]);
	if (execve(path->binary[0], path->cmd[0], NULL) == -1)
		show_error(path, "Execve failed");
	return ;
}

static void	parent_patern(t_path *path, int *pipefd)
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		show_error(path, "Dup2 failed");
	if (dup2(path->fd_2, STDOUT_FILENO) == -1)
		show_error(path, "Dup2 failed");
	close(pipefd[0]);
	waitpid(-1, NULL, 0);
	if (execve(path->binary[1], path->cmd[1], NULL) == -1)
		show_error(path, "Execve failed");
	return ;
}

void	pipex(t_path *path)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		show_error(path, "Pipe failed");
	pid = fork();
	if (pid == -1)
		show_error(path, "Fork failed");
	if (pid == 0)
		children_patern(path, pipefd);
	else
		parent_patern(path, pipefd);
}

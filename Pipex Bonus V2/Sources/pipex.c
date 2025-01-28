/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:12:23 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/28 14:42:04 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	children_patern_1(t_path *path, int *pipefd)
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

static void	children_partern_2(t_path *path, int *pipefd)
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		show_error(path, "Dup2 failed");
	if (dup2(path->fd_2, STDOUT_FILENO) == -1)
		show_error(path, "Dup2 failed");
	close(pipefd[0]);
	if (execve(path->binary[1], path->cmd[1], NULL) == -1)
		show_error(path, "Execve failed");
	return ;
}

void	pipex(t_path *path)
{
	int		status;
	pid_t	pid_1;
	pid_t	pid_2;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		show_error(path, "Pipe failed");
	pid_1 = fork();
	if (pid_1 == -1)
		show_error(path, "Fork failed");
	if (pid_1 == 0)
		children_patern_1(path, pipefd);
	pid_2 = fork();
	if (pid_2 == -1)
		show_error(path, "Fork failed");
	if (pid_2 == 0)
		children_partern_2(path, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_1, &status, 0);
	waitpid(pid_2, &status, 0);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:12:23 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/29 19:08:15 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	children_patern_1(t_path *path, int *pipefd)
{
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		show_error(path, "dup2 failed");
	close(pipefd[1]);
	if (dup2(path->fd_1, STDIN_FILENO) == -1)
		show_error(path, "dup2 failed");
	close(path->fd_1);
	if (execve(path->binary[0], path->cmd[0], NULL) == -1)
		show_error(path, "execve failed");
}

static void	children_partern_2(t_path *path, int *pipefd)
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		show_error(path, "dup2 failed");
	close(pipefd[0]);
	if (dup2(path->fd_2, STDOUT_FILENO) == -1)
		show_error(path, "dup2 failed");
	close(path->fd_2);
	if (execve(path->binary[1], path->cmd[1], NULL) == -1)
		show_error(path, "execve failed");
}

static void parent_partern(t_path *path, int *pipefd, pid_t pid_1, pid_t pid_2)
{
	int status_1;
	int status_2;
	
	close(pipefd[0]);
	close(pipefd[1]);

    waitpid(pid_1, &status_1, 0);
	waitpid(pid_2, &status_2, 0);
    if (WIFEXITED(status_1) && WEXITSTATUS(status_1) != 0)
		show_error(path, "Error in children 1");
	if (WIFEXITED(status_2) && WEXITSTATUS(status_2) != 0)
		show_error(path, "Error in children 2");
}

void	pipex(t_path *path)
{
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
	parent_partern(path, pipefd, pid_1, pid_2);
	return ;
}

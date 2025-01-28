/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:12:23 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/28 13:43:03 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	fd_here_doc(t_path *path)
{
	char	*line;

	path->fd_1 = open(".here_doc.fd", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (path->fd_1 == -1)
		show_error(path, "Open here_doc file failed");
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			show_error(path, "Get_next_line failed");
		if (ft_strncmp(line, path->limiter, ft_strlen(line) - 1) == 0
			&& (ft_strncmp(line, path->limiter, ft_strlen(path->limiter)) == 0))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, path->fd_1);
		free(line);
	}
	close(path->fd_1);
	path->fd_1 = open(".here_doc.fd", O_RDONLY);
	if (path->fd_1 == -1)
		show_error(path, "Open here_doc file failed");
}

static void	children_patern(t_path *path, int *pipefd, int i)
{
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		show_error(path, "Dup2 failed");
	close(pipefd[1]);
	if (execve(path->binary[i], path->cmd[i], NULL) == -1)
		show_error(path, "Execve failed");
	return ;
}

static void	parent_patern(t_path *path, int *pipefd, pid_t pid)
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		show_error(path, "Dup2 failed");
	close(pipefd[0]);
	waitpid(pid, NULL, 0);
	return ;
}

static void	pipe_patern(t_path *path, int i)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		show_error(path, "Pipe failed");
	pid = fork();
	if (pid == -1)
		show_error(path, "Fork failed");
	if (pid == 0)
		children_patern(path, pipefd, i);
	else
		parent_patern(path, pipefd, pid);
}

void	pipex(t_path *path)
{
	int	i;

	i = 0;
	if (path->here_doc)
		fd_here_doc(path);
	if (dup2(path->fd_1, STDIN_FILENO) == -1)
		show_error(path, "Dup2 failed");
	close(path->fd_1);
	while (i < path->cmd_nbr - 1)
	{
		pipe_patern(path, i);
		i++;
	}
	if (dup2(path->fd_2, STDOUT_FILENO) == -1)
		show_error(path, "Dup2 failed");
	close(path->fd_2);
	unlink(".here_doc.fd");
	if (execve(path->binary[i], path->cmd[i], NULL) == -1)
		show_error(path, "Execve failed");
}

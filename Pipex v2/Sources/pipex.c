/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:39 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/22 16:52:35 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_limiter(t_path *path)
{
	char	*line;
	int		limiter_len;
	int		fd;


	fd = open("Temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		show_error(path, "Open path->fd_1 failed");
	limiter_len = ft_strlen(path->limiter);
	ft_printf("%s\n", path->limiter);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, path->limiter, limiter_len) == 0)
		{
			free(line);
			path->fd_1 =open("Temp", O_RDONLY);
			return ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	show_error(path, "here_doc failed");
}

static void	parent_patern(t_path *path, int pipe_fd[2])
{
	int	status;
	int	bin;

	bin = path->bin + 1;
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		show_error(path, "Dup2 parent 1 failed");
	if (dup2(path->fd_2, STDOUT_FILENO) == -1)
		show_error(path, "Dup2 parent 2 failed");
	close(pipe_fd[0]);
	waitpid(-1, &status, 0);
	if (execve(path->binary[bin], path->cmd[bin], NULL) == -1)
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

	if (path->here_doc == 1)
		check_limiter(path);
	if (pipe(pipe_fd) == -1)
		show_error(path, "Pipe failed");
	pid = fork();
	if (pid == -1)
		show_error(path, "Fork failed");
	if (pid == 0)
		child_patern(path, pipe_fd);
	else
		parent_patern(path, pipe_fd);
	close (pipe_fd[0]);
	close (pipe_fd[1]);
	if (unlink("Temp") < 0)
		show_error(path, "Unlink failed");
	return ;
}

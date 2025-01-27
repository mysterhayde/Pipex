/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:15:57 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/23 17:00:59 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	parent_fork(t_path *path, int pipe_fd[2], int fd_test)
{
	int	nb;
	int status;

	nb = path->bin_nb + 1;
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		show_error(path, "dup2 parent failed");
	if (dup2(path->fd_output, STDOUT_FILENO) == -1)
		show_error(path, "dup2 parent failed");
	waitpid(-1, &status, 0);
	ft_putstr_fd("test parent\n", fd_test);
	if (execve(path->binary[nb], path->cmd[nb], NULL) == -1)
		show_error(path, "Execve failed");
	return;
}

static void	children_fork(t_path *path, int pipe_fd[2])
{
	close(pipe_fd[0]);
	if (dup2(path->fd_input, STDIN_FILENO) == -1)
		show_error(path, "Dup2 child1 failed");
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		show_error(path, "Dup2 child2 failed");
	close(pipe_fd[1]);
	if (execve(path->binary[path->bin_nb], path->cmd[path->bin_nb], NULL) == -1)
		show_error(path, "Execve failed");
	return ;
}

static void	here_doc_input(t_path *path, char **argv)
{
	char	*line;
	int		limiter_len;
	int		len;

	limiter_len = ft_strlen(argv[2]);
	path->fd_input = open("here_doc.fd", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (path->fd_input == -1)
		show_error(path, "Open here_doc file failed");
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			show_error(path, "Get_next_line failed");
		len = (ft_strlen(line) - 1);
		if (limiter_len > len)
			len = limiter_len;
		if (ft_strncmp(line, path->limiter, len) == 0)
		{
			free(line);
			return ;
		}
		ft_putstr_fd(line, path->fd_input);
		free(line);
	}
}

void	pipex(t_path *path, char **argv)
{
	int fd_test = open("test.txt", O_WRONLY);
	if (fd_test == -1)
		show_error(path, "Fd_test failed");
	ft_putstr_fd("test input\n", fd_test);

	int		pipe_fd[2];
	pid_t	pid;

	if (path->here_doc == 1)
		here_doc_input(path, argv);
	else
	{
		path->fd_input = open(argv[1], O_RDONLY);
		if (path->fd_input == -1)
			show_error(path, "Open file input failed");
	}
	if (pipe(pipe_fd) == -1)
		show_error(path, "Pipe failed");
	pid = fork();
	if (pid == -1)
		show_error(path, "Fork failed");
	if (pid == 0)
		children_fork(path, pipe_fd);
	else
		parent_fork(path, pipe_fd, fd_test);
	write(fd_test, "test output\n", 13);
	exit(EXIT_FAILURE);
}

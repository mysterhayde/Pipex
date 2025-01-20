/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:39 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/20 11:31:27 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_path *path)
{
	int	pipe_fd[2];
	pid_t pid;

	if (pipe(pipe_fd) == -1)
		show_error("Pipe failed");
	
	pid = fork();
	if (pid == -1)
		show_error("Fork failed");

	if (execve(path->binary[0], path->cmd[0], NULL) == -1)
		show_error ("execve failed");
	return ;
}
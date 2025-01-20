/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:13:03 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/20 13:25:36 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int fd[2];
	pid_t pid;
	char buffer[13];

	if(pipe(fd) == -1)
		printf("Error pipe\n");

	pid = fork();
	if (pid == -1)
		printf("Error PID\n");
		
	if (pid == 0)
	{
		close(fd[0]);
		write(fd[1], "Hello Wolrd", 11);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		read(fd[0], buffer, 13);
		close(fd[0]);
		printf("message de l'enfant, '%s'\n", buffer);
		exit(EXIT_SUCCESS);
	}
}
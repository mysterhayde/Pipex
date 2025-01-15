/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:07:38 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/15 20:12:40 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void check_arguments(int argc, char **argv)
{
	if (argc != 5)
	{
		if (argc > 5)
			ft_putendl_fd("Error\nToo mouch arguments", 2);
		else if (argc < 5)
			ft_putendl_fd("Error\nNot enough arguments", 2);
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], R_OK) == -1)
	{
		perror("Error\nFile 1");
		exit(EXIT_FAILURE);
	}
	if (access(argv[2], X_OK) == -1)
	{
		perror("Error\nCmd 1");
		exit(EXIT_FAILURE);
	}
	if (access(argv[3], X_OK) == -1)
	{
		perror("Error\nCmd 2");
		exit(EXIT_FAILURE);
	}
	if (access(argv[4], W_OK) == -1)
	{
		perror("Error\nFile 2");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	
	check_arguments(argc, argv);
	return (0);
}

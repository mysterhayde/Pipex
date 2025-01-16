/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:23:44 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/16 17:05:14 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	show_error(char *str)
{
	ft_putendl_fd(COLOR_RED"Error", 2);
	perror(str);
	ft_putendl_fd(COLOR_RESET, 2);
	exit(EXIT_FAILURE);
}

static void	check_args(char **envp, char **argv, int argc)
{
	int	i;

	i = 0;
	if (access(argv[1], R_OK) == -1)
		show_error("Cannot open input file");
	if (access(argv[argc - 1], W_OK) == -1)
		show_error("Cannot open output_file");
	while (envp[i])
	{
		
	}
	
	
}

int main(int argc, char **argv, char **envp)
{
	if (argc < 4)
	{
		ft_putendl_fd("Error not enough args", 2);
		exit(EXIT_FAILURE);
	}
	check_args(envp, argv, argc);
	return (0);
}
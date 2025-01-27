/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:23:44 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/27 10:00:08 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	show_error(t_path *path, char *str)
{
	ft_putendl_fd(COLOR_RED"Error", 2);
	perror(str);
	ft_putendl_fd(COLOR_RESET, 2);
	free_struct(path);
	exit(EXIT_FAILURE);
}


int main(int argc, char **argv, char **envp)
{
	t_path	path;

	if (argc < 5)
	{
		ft_putendl_fd(COLOR_RED"Not enough args"COLOR_RESET, 2);
		exit(EXIT_FAILURE);
	}
	init_struct(&path, argc, argv);
	path.path = get_path(&path, envp);
	get_cmd(&path, argc, argv);
	pipex(&path);
	free_struct(&path);
	return (0);
}

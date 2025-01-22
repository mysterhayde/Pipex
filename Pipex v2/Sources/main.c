/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:23:44 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/22 15:05:42 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	show_error(t_path *path, char *str)
{
	ft_putendl_fd(COLOR_RED"Error", 2);
	perror(str);
	ft_putstr_fd(COLOR_RESET, 2);
	free_struct(path);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_path	path;

	if (argc < 5)
	{
		ft_putendl_fd(COLOR_RED"Not enough args"COLOR_RESET, 2);
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
		{
			ft_putendl_fd(COLOR_RED"Not enough args"COLOR_RESET, 2);
			exit(EXIT_FAILURE);
		}
		init_struct(&path, argc, argv, 1);
	}
	else
		init_struct(&path, argc, argv, 0);
	path.path = get_path(&path, envp, argv, argc);
	get_cmd(&path, argc, argv);
	pipex(&path);
	free_struct(&path);
	return (0);
}

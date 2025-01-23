/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:24:50 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/23 16:49:30 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	show_error(t_path *path, char *str)
{
	ft_putendl_fd(COLOR_RED"Error", 2);
	perror(str);
	ft_putendl_fd(COLOR_RESET, 2);
	//free_struct(path);
	exit(EXIT_FAILURE);
}

static void	check_args(t_path *path, char **argv, int argc)
{
	if (path->here_doc == 1)
	{
		if (argc < 6)
			show_error(path, "Not enought args");
		path->fd_output = open(argv[argc - 1], O_WRONLY | O_CREAT, 0644);
		if (path->fd_output == -1)
			show_error(path, "Open fd_output failed");
	}
	else
	{
		if (access(argv[1], F_OK | R_OK) == -1)
			show_error(path, "Input file");
		path->fd_output = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (path->fd_output == -1)
			show_error(path, "Open fd_output failed");
	}
	if (access(argv[argc - 1], F_OK | W_OK) == -1)
		show_error(path, "Output file");
	
}

void	check_here_doc(t_path *path, int argc, char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		path->here_doc = 1;
		path->cmd_nbr = argc - 4;
		path->cmd_pos = 3;
		path->limiter = argv[2];
	}
	else
	{
		path->here_doc = 0;
		path->cmd_nbr = argc - 3;
		path->cmd_pos = 2;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_path	path;
	
	if (argc < 5)
		show_error(&path, "Not enought args");
	check_here_doc(&path, argc, argv);
	init_struct(&path);
	check_args(&path, argv, argc);
	path.path = get_all_path(&path, argc, argv, envp);
	get_cmd(&path, argc, argv);
	pipex(&path, argv);
	printf("%s\n", "program END");
}

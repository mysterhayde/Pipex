/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:06:11 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/28 13:39:46 by hdougoud         ###   ########.fr       */
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

void	check_args(t_path *path, int argc, char **argv)
{
	path->fd_1 = open(argv[1], O_RDONLY);
	if (path->fd_1 == -1)
		show_error(path, "Open fd_1 failed");
	path->fd_2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (path->fd_2 == -1)
		show_error(path, "Open fd_2 failed");
}

static void	init_struct(t_path *path)
{
	path->path = NULL;
	path->cmd = NULL;
	path->binary = NULL;
	path->cmd_nbr = 2;
	path->cmd_pos = 2;
	path->fd_1 = 0;
	path->fd_2 = 0;
	path->cmd = malloc(sizeof(char **) * (path->cmd_nbr + 1));
	if (!path->cmd)
		show_error(path, "Malloc path->cmd failed");
	path->binary = malloc(sizeof(char *) * (path->cmd_nbr + 1));
	if (!path->binary)
		show_error(path, "Malloc path->binary failed");
}

int	main(int argc, char **argv, char **envp)
{
	t_path	path;

	if (argc != 5)
	{
		ft_putendl_fd(COLOR_RED"Wrong args numbers"COLOR_RESET, 2);
		exit(EXIT_FAILURE);
	}
	init_struct(&path);
	check_args(&path, argc, argv);
	path.path = get_all_path(&path, envp);
	get_cmd(&path, argv);
	pipex(&path);
	exit(EXIT_SUCCESS);
}

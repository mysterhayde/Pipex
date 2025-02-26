/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:06:11 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/29 19:32:36 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	show_error(t_path *path, char *str)
{
	ft_putendl_fd(COLOR_RED"Error", 2);
	perror(str);
	ft_putendl_fd(COLOR_RESET, 2);
	free_struct(path);
	exit(EXIT_FAILURE);
}

static void	init_struct(t_path *path, int argc)
{
	path->path = NULL;
	path->cmd = NULL;
	path->binary = NULL;
	path->cmd_nbr = (argc - 3 - path->here_doc);
	path->cmd_pos = (2 + path->here_doc);
	path->fd_1 = 0;
	path->fd_2 = 0;
	path->cmd = ft_calloc(sizeof(char **), (path->cmd_nbr + 1));
	if (!path->cmd)
		show_error(path, "Malloc path->cmd failed");
	path->binary = ft_calloc(sizeof(char *), (path->cmd_nbr + 1));
	if (!path->binary)
		show_error(path, "Malloc path->binary failed");
}

static void	check_args(t_path *path, int argc, char **argv)
{
	if (path->here_doc == 0)
	{
		path->fd_1 = open(argv[1], O_RDONLY);
		if (path->fd_1 == -1)
			show_error(path, "Open fd_1 failed");
		path->fd_2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (path->fd_2 == -1)
			show_error(path, "Open fd_2 failed");
	}
	else
	{
		path->fd_2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (path->fd_2 == -1)
			show_error(path, "Open fd_2 failed");
		path->limiter = argv[2];
	}
}

static void	here_docs(t_path *path, char **argv, int argc)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		path->here_doc = 1;
	else
	{
		if (argc < 6)
		{
			ft_putendl_fd(COLOR_RED"Not enough args"COLOR_RESET, 2);
			exit(EXIT_FAILURE);
		}
		path->here_doc = 0;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_path	path;

	if (argc < 5)
	{
		ft_putendl_fd(COLOR_RED"Not enough args"COLOR_RESET, 2);
		exit(EXIT_FAILURE);
	}
	here_docs(&path, argv, argc);
	init_struct(&path, argc);
	check_args(&path, argc, argv);
	path.path = get_all_path(&path, envp);
	get_cmd(&path, argv);
	pipex(&path);
	exit(EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:34:23 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/22 15:14:31 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	load_here_foc(t_path *path, int argc, char **argv)
{
	path->cmd = malloc(sizeof(char **) * argc - 3);
	if (!path->cmd)
		show_error(path, "Malloc path->cmd failed");
	path->binary = malloc(sizeof(char **) * argc - 2);
	if (!path->binary)
		show_error(path, "Malloc path->binary failed");
	path->fd_2 = open(path->file_2, O_WRONLY | O_CREAT , 0644);
	if (path->fd_2 == -1)
		show_error(path, "Open output file failed");
	path->limiter = argv[2];
	path->here_doc = 1;
}

void	load_file_1(t_path *path, int argc, char **argv)
{
	path->cmd = malloc(sizeof(char **) * argc - 2);
	if (!path->cmd)
		show_error(path, "Malloc path->cmd failed");
	path->binary = malloc(sizeof(char **) * argc - 2);
	if (!path->binary)
		show_error(path, "Malloc path->binary failed");
	path->file_1 = argv[1];
	path->fd_1 = open(path->file_1, O_RDONLY);
	if (path->fd_1 == -1)
		show_error(path, "Open input file failed");
	path->fd_2 = open(path->file_2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (path->fd_2 == -1)
		show_error(path, "Open output file failed");
	path->here_doc = 0;
}

void	init_struct(t_path *path, int argc, char **argv, int param)
{
	path->bin = 0;
	path->fd_1 = 0;
	path->fd_2 = 0;
	path->cmd = NULL;
	path->path = NULL;
	path->binary = NULL;
	path->file_2 = argv[argc - 1];
	if (param == 0)
		load_file_1(path, argc, argv);
	else
		load_here_foc(path, argc, argv);
}

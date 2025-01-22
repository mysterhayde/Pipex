/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:34:23 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/22 11:06:38 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(t_path *path, char **argv)
{
	exit(EXIT_SUCCESS);
}

void	load_file_1(t_path *path, char **argv)
{
	path->file_1 = argv[1];
	path->fd_1 = open(path->file_1, O_RDONLY);
}

void	init_struct(t_path *path, int argc, char **argv, int param)
{
	path->binary = NULL;
	path->cmd = NULL;
	path->path = NULL;
	path->file_2 = argv[argc - 1];
	path->binary = malloc(sizeof(char * ) * argc - 2);
	if (!path->binary)
		show_error(path, "Malloc path->binary failed");
	path->binary[argc - 3] = NULL;
	path->cmd = malloc(sizeof(char *) * (argc - 2));
	if (!path->cmd)
		show_error(path, "Malloc path->cmd failed");
	path->cmd[argc - 3] = NULL;
	path->bin = 0;
	if (param == 0)
		here_doc(path, argv);
}
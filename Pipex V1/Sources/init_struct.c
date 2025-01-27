/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:34:23 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/27 10:10:45 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(t_path *path, int argc, char **argv)
{
	path->binary = NULL;
	path->cmd = NULL;
	path->path = NULL;
	path->file_1 = argv[1];
	path->file_2 = argv[argc - 1];
	path->fd_1 = open(path->file_1, O_RDONLY);
	if (path->fd_1 == -1)
		show_error(path, "Open fd_1 failed");
	path->fd_2 = open(path->file_2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (path->fd_2 == -1)
		show_error(path, "Open fd_2 failed");
	path->binary = malloc(sizeof(char *) * argc - 2);
	if (!path->binary)
		show_error(path, "Malloc path->binary failed");
	path->cmd = malloc(sizeof(char *) * (argc - 2));
	if (!path->cmd)
		show_error(path, "Malloc path->cmd failed");
	path->bin = 0;
}

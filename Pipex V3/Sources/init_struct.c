/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:06:53 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/23 15:11:53 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(t_path *path)
{
	path->cmd = NULL;
	path->path = NULL;
	path->binary = NULL;
	path->binary = malloc(sizeof(char *) * (path->cmd_nbr + 1));
	if (!path->binary)
		show_error(path, "Malloc path->binary failed");
	path->cmd = malloc(sizeof(char **) * path->cmd_nbr + 1);
	if (!path->cmd)
		show_error(path, "Malloc path->cmd failed");
	path->bin_nb = 0;
}
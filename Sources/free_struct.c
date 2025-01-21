/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_strcut.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:54:38 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/21 16:55:27 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_struct(t_path *path)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (path->path[i])
		free(path->path[i++]);
	free(path->path);
	i = 0;
	free(path->cmd);
	while(path->binary[i])
		free(path->binary[i++]);
	free(path->binary);
	i = 0;
	while(path->cmd[j])
	{
		while(path->cmd[j][i])
			free(path->cmd[j][i++]);
		i = 0;
		j++;
	}
	close (path->fd_1);
	close (path->fd_2);
}
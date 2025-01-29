/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:10:39 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/29 19:17:41 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_struct(t_path *path)
{
	int	i;

	i = 0;
	if (path->path)
		free_tab(path->path);
	if (path->binary)
		free_tab(path->binary);
	if (path->cmd)
	{
		while (path->cmd[i])
			free_tab(path->cmd[i++]);
		free(path->cmd);
		path->cmd = NULL;
	}
	if (path->fd_1 > 0)
		close(path->fd_1);
	if (path->fd_2 > 0)
		close(path->fd_2);
	return ;
}

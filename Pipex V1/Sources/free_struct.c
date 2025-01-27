/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:54:38 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/27 09:50:58 by hdougoud         ###   ########.fr       */
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
		i++;
	}
	free(tab);
}

static void	free_cmd(t_path *path)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (path->cmd[j])
	{
		while (path->cmd[j][i])
			free(path->cmd[j][i++]);
		i = 0;
		free(path->cmd[j]);
		j++;
	}
	free(path->cmd);
}

void	free_struct(t_path *path)
{
	if (path->path)
		free_tab(path->path);
	if (path->binary)
		free_tab(path->binary);
	if (path->cmd)
		free_cmd(path);
	if (path->fd_1)
		close(path->fd_1);
	if (path->fd_2)
		close(path->fd_2);
}

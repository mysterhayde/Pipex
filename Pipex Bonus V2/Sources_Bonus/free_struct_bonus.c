/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:10:39 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/29 19:16:35 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	free_struct(t_path *path)
{
	int	i;

	i = 0;
	if (path->path)
		free_tab(path->path);
	if (path->binary)
		free_tab(path->binary);
	while (path->cmd[i])
		free_tab(path->cmd[i++]);
	free(path->cmd);
	if (path->fd_1 > 0)
		close(path->fd_1);
	if (path->fd_2 > 0)
		close(path->fd_2);
	return ;
}

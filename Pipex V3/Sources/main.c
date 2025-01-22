/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:24:50 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/22 19:32:17 by hdougoud         ###   ########.fr       */
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

int main(int argc, char **argv, char **envp)
{
	t_path	path;

	if (argc < 5)
		show_error(&path, "Not enough args");
	path.path = get_path(&path, envp, argv, argc);
	return (0);
}
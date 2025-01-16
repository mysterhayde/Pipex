/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:21:10 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/16 15:16:09 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_pipe(int argc, char **argv)
{
	int fd_1;
	int	fd_2;

	fd_1 = open(argv[1], O_RDONLY);
	if (fd_1 == -1)
		show_errors(CANNOT_ACCES);
	
}
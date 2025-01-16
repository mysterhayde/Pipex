/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:39:20 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/16 15:45:38 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	show_errors(t_binary *binary, int error)
{
	ft_putendl_fd(COLOR_RED"Error", 2);
	if (error == CANNOT_ACCES)
		perror("Cannot acces to the file");
	else if (error == MALLOC_ERROR)
		(perror("the program can't malloc"));
	else if (error == TOO_MUCH_ARGS)
		ft_putendl_fd(COLOR_YELLOW"Too much args", 2);
	else if (error == NOT_ENOUGH_ARGS)
		ft_putendl_fd(COLOR_YELLOW"Not enough args", 2);
	ft_putstr_fd(COLOR_RESET, 2);
	exit(EXIT_FAILURE);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:07:53 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/16 16:13:09 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "../libft/libft.h"

# define MALLOC_ERROR		0
# define CANNOT_ACCES		1
# define TOO_MUCH_ARGS		2
# define NOT_ENOUGH_ARGS	3

typedef struct s_binary
{
	char	**cmd;
}			t_binary;

void	show_errors(t_binary *binary, int error);
void	find_binary(t_binary *binary, char *str);
void	clean_exit(t_binary *binary, int exit_status, int argc);

#endif 
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:22:55 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/17 18:11:33 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "../libft/libft.h"

typedef struct s_path
{
	char		**path;
	char		***cmd;
	const char	*file_1;
	const char	*file_2;
}	t_path;

void	pipex(t_path *path);
void	show_error(char *str);
void	get_binary(t_path *path, int argc, char **argv);
char	**get_path(char **envp, char **argv, int argc);

#endif 
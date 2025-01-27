/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:22:55 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/27 10:12:07 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/wait.h>

typedef struct s_path
{
	char		**path;
	char		***cmd;
	char		**binary;
	int			bin;
	int			fd_1;
	int			fd_2;
	const char	*file_1;
	const char	*file_2;
}	t_path;

void	pipex(t_path *path);
void	free_struct(t_path *path);
void	show_error(t_path *path, char *str);
void	get_cmd(t_path *path, int argc, char **argv);
void	init_struct(t_path *path, int argc, char **argv);
char	**get_path(t_path *path, char **envp);
#endif
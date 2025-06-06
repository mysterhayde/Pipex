/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:22:55 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/31 21:11:50 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H



# include "../libft/libft.h"
# include <sys/wait.h>

typedef struct s_path
{
	char	**path;
	char	***cmd;
	char	**binary;
	int		fd_1;
	int		fd_2;
	int		cmd_nbr;
	int		cmd_pos;
}	t_path;

void	pipex(t_path *path);
void	free_struct(t_path *path);
void	get_cmd(t_path *path, char **argv);
void	show_error(t_path *path, char *str);

char	**get_all_path(t_path *path, char **envp);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:25:40 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/23 15:11:20 by hdougoud         ###   ########.fr       */
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
	char		*limiter;
	int			bin_nb;
	int			cmd_nbr;
	int			cmd_pos;
	int			here_doc;
	int			fd_input;
	int			fd_output;
}	t_path;

void	init_struct(t_path *path);
void	pipex(t_path *path, char **argv);
void	show_error(t_path *path, char *str);
void	get_cmd(t_path *path, int argc, char **argv);
char	**get_all_path(t_path *path, int argc, char **argv, char **envp);
#endif
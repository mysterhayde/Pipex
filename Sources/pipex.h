/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:22:55 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/20 11:19:30 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "../libft/libft.h"

typedef struct s_path
{
	char		**path;
	char		***cmd;
	char		**binary;
	const char	*file_1;
	const char	*file_2;
}	t_path;

void	pipex(t_path *path);
void	show_error(char *str);
void	get_cmd(t_path *path, int argc, char **argv);
char	**get_path(char **envp, char **argv, int argc);

#endif 
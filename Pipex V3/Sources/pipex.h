/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:25:40 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/22 19:26:52 by hdougoud         ###   ########.fr       */
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

#endif
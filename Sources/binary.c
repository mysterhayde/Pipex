/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:46:36 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/17 21:23:47 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_binary(t_path *path, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc - 3)
	{
		if (!path || !path->cmd)
			show_error("invalid struct");
		path->cmd[i] = ft_split(argv[i + 2], ' ');
			if (!path->cmd[i])
				show_error("Cannot find binary");
		i++;
	}
	path->cmd[i] = NULL;
}

char	**get_path(char **envp, char **argv, int argc)
{
	int		i;
	char	*env;
	char	**path;

	i = 0;
	while (envp[i])
	{
		if ((env = ft_strnstr(envp[i], "PATH=", 5)) != NULL)
			break;
		i++;	
	}
	if (!env)
		show_error("Cannot find PATH in env");
	path = ft_split(env, ':');
	return (path);
}


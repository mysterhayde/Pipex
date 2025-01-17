/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:46:36 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/17 18:10:37 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char **get_binary_flag(t_path *path, char *argv, int j)
{
	int i;

	i = 0;
	path->cmd[j] = ft_split(argv, ' ');
	while (path->cmd[j][i])
	{
		path->cmd[j][i] = ft_strtrim(path->cmd[j][i], " ");
		i++;
	}
	
	return (path->cmd[j]);
}

void	get_binary(t_path *path, int argc, char **argv)
{
	int		i;
	char	**cmd;

	i = 0;
	while (i < argc - 3)
	{
		cmd = get_binary_flag(path, argv[i + 2], i);
			if (!cmd)
				show_error("Cannot find binary");
		path->cmd[i] = cmd;
		i++;
	}
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


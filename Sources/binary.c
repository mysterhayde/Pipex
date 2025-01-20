/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:46:36 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/20 11:27:54 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_binary(t_path *path, char *cmd)
{
	int 	i;
	char	*bin;
	char	*tmp;

	i = 0;
	while(path->path[i])
	{
		tmp = ft_strjoin(path->path[i++], "/");
		bin = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(bin, F_OK) >= 0)
		{
			if (access(bin, X_OK) >= 0)
				break ;
			else
				show_error("invalid permission to access binary");
		}
		free(bin);
	}
	if (!path->path[i])
		show_error("Cannot find binary");
	return (bin);
}

void	get_cmd(t_path *path, int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < argc - 3)
	{
		if (!path || !path->cmd)
			show_error("invalid struct");
		path->cmd[i] = ft_split(argv[i + 2], ' ');
		if (!path->cmd[i])
			show_error("Malloc path->cmd failed");
		path->binary[i] = get_binary(path, path->cmd[i][0]);
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
	env += 5;
	path = ft_split(env, ':');
	return (path);
}


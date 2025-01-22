/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:46:36 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/22 16:04:59 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_binary(t_path *path, char *cmd)
{
	int		i;
	char	*bin;
	char	*tmp;

	i = 0;
	while (path->path[i])
	{
		tmp = ft_strjoin(path->path[i++], "/");
		bin = ft_strjoin(tmp, cmd);
		//safe_free((void *) &tmp);
		if (access(bin, F_OK) >= 0)
		{
			if (access(bin, X_OK) >= 0)
				break ;
			else
				show_error(path, "invalid permission to access binary");
		}
		//safe_free((void *) &bin);
	}
	if (!path->path[i])
		show_error(path, "Cannot find binary");
	return (bin);
}

void	get_cmd(t_path *path, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < (argc - 3 - path->here_doc)) //CHECK NUMBER HERE
	{
		if (!path || !path->cmd)
			show_error(path, "invalid struct");
		path->cmd[i] = ft_split(argv[i + 2 + path->here_doc], ' ');
		if (!path->cmd[i])
			show_error(path, "Malloc path->cmd failed");
		path->binary[i] = get_binary(path, path->cmd[i][0]);
		i++;
	}
	path->cmd[i] = NULL;
}

char	**get_path(t_path *path, char **envp, char **argv, int argc)
{
	int		i;
	char	*env;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		env = ft_strnstr(envp[i], "PATH=", 5);
		if (env != NULL)
			break ;
		i++;
	}
	if (!env)
		show_error(path, "Cannot find PATH in env");
	env += 5;
	paths = ft_split(env, ':');
	return (paths);
}

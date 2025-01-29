/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:32:27 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/29 18:51:58 by hdougoud         ###   ########.fr       */
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
		if (!tmp)
			show_error(path, "Malloc failed");
		bin = ft_strjoin(tmp, cmd);
		if (!bin)
			show_error(path, "Malloc failed");
		safe_free((void *) &tmp);
		if (access(bin, F_OK) >= 0)
		{
			if (access(bin, X_OK) >= 0)
				return (bin);
			else
				show_error(path, "invalid permission to access binary");
		}
		safe_free((void *) &bin);
	}
	show_error(path, "Cannot find binary");
	return (NULL);
}

void	get_cmd(t_path *path, char **argv)
{
	int	i;

	i = 0;
	while (i < (path->cmd_nbr))
	{
		if (!path || !path->cmd)
			show_error(path, "invalid struct");
		path->cmd[i] = ft_split(argv[i + path->cmd_pos], ' ');
		if (!path->cmd[i])
			show_error(path, "Malloc path->cmd failed");
		path->binary[i] = get_binary(path, path->cmd[i][0]);
		i++;
	}
	path->cmd[i] = NULL;
	path->binary[i] = NULL;
}

char	**get_all_path(t_path *path, char **envp)
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
		show_error(path, "Cannot find 'PATH'");
	env += 5;
	paths = ft_split(env, ':');
	if (!paths)
		show_error(path, "Split failed");
	return (paths);
}

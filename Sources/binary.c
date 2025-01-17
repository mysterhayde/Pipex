/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:46:36 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/17 14:11:19 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path_cmd(char **path, char *argv)
{
	int		i;
	char	*tmp;
	char	*cmd;

	i = 0;
	while(path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(tmp, argv);
		free(tmp);
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		free(cmd);
		i++;
	}
	return (NULL);
}


static char *get_binary_flag(t_path *path, char *argv, int j)
{
	int		i;
	char	*flag;
	char	*cmd;

	i = 0;
	flag = argv;
	while(argv[i] && argv[i] != ' ')
		i++;
	if (!argv[i])
	{
		path->flag[j] = NULL;
		return(argv);
	}
	flag += i + 1;
	path->flag[j] = flag;
	cmd = argv;
	cmd[i] = '\0';
	return (cmd);		//Warning with free here
}

void	get_binary(t_path *path, int argc, char **argv)
{
	int		i;
	char	*cmd;

	i = 0;
	while (i < argc - 3)
	{
		cmd = get_binary_flag(path, argv[i + 2], i);
		cmd = get_path_cmd(path->path, argv[i + 2]);
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


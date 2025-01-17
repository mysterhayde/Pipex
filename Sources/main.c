/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:23:44 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/17 15:01:10 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	show_error(char *str)
{
	ft_putendl_fd(COLOR_RED"Error", 2);
	perror(str);
	ft_putendl_fd(COLOR_RESET, 2);
	exit(EXIT_FAILURE);
}

static void	check_files(int argc, char **argv, t_path *path)
{
	int		i;
	int		j;
	char 	*tmp;
	char	*cmd;

	i = 0;
	j = 0;
	if (access(argv[1], F_OK | R_OK) == -1)
		show_error("Cannot open input file");
	if (access(argv[argc - 1], F_OK | W_OK) == -1)
		show_error("Cannot open output file");
}

static void	init_struct(t_path *path, int argc, char **argv, char **envp)
{
	path->path = get_path(envp, argv, argc);
	path->cmd = malloc(sizeof(char *) * (argc - 2));
	if (!path->cmd)
		show_error("Malloc failed");
	path->cmd[argc - 2] = NULL;
	path->flag = malloc(sizeof(char *) * (argc - 2)); 
	if (!path->flag)
		show_error("Malloc failed");
	path->flag[argc - 2] = NULL;
	path->file_1 = argv[1];
	path->file_2 = argv[argc - 1];
}

int main(int argc, char **argv, char **envp)
{
	t_path	path;
	
	if (argc < 4)
	{
		ft_putendl_fd("Error not enough args", 2);
		exit(EXIT_FAILURE);
	}
	init_struct(&path, argc, argv, envp);
	check_files(argc, argv, &path);
	get_binary(&path, argc, argv);
	
	int i = 0;
	while (path.cmd[i])
	{
		printf("%s %s\n", path.cmd[i], path.flag[i]);
		i++;
	}
	pipex(&path);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:23:44 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/21 13:24:04 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_struct(t_path *path)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (path->path[i])
		free(path->path[i++]);
	free(path->path);
	i = 0;
	free(path->cmd);
	while(path->binary[i])
		free(path->binary[i++]);
	free(path->binary);
	i = 0;
	while(path->cmd[j])
	{
		while(path->cmd[j][i])
			free(path->cmd[j][i++]);
		i = 0;
		j++;
	}
}

void	show_error(t_path *path, char *str)
{
	ft_putendl_fd(COLOR_RED"Error", 2);
	perror(str);
	ft_putendl_fd(COLOR_RESET, 2);
	free_struct(path);
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
		show_error(path, "Cannot open input file");
	if (access(argv[argc - 1], F_OK | W_OK) == -1)
		show_error(path, "Cannot open output file");
	path->fd_2 = open("output.txt", O_WRONLY);
	if (path->fd_2 == -1)
		show_error(path, "Open fd_2 failed");
	path->fd_1 = open("input.txt", O_RDONLY);
	if (path->fd_1 == -1)
		show_error(path, "Open fd_1 failed");
}

static void	init_struct(t_path *path, int argc, char **argv, char **envp)
{
	path->path = get_path(path, envp, argv, argc);
	path->binary = malloc(sizeof(char * ) * argc - 2);
	if (!path->binary)
		show_error(path, "Malloc path->binary failed");
	path->binary[argc - 3] = NULL;
	path->cmd = malloc(sizeof(char *) * (argc - 2));
	if (!path->cmd)
		show_error(path, "Malloc path->cmd failed");
	path->cmd[argc - 3] = NULL;
	path->file_1 = argv[1];
	path->file_2 = argv[argc - 1];
	path->fd_1 = 0;
	path->fd_2 = 0;
	path->bin = 0;
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
	get_cmd(&path, argc, argv);
	
	int i = 0;
	int	j = 0;
	while (path.cmd[i])
	{
		while(path.cmd[i][j])
			printf("%s ", path.cmd[i][j++]);
		printf("\n");
		j = 0;
		i++;
	}
	pipex(&path);
	free_struct(&path);
	return (0);
}

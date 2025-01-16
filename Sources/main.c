/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:23:44 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/16 23:25:23 by hdougoud         ###   ########.fr       */
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



static void	check_args(int argc, char **argv, t_path *path)
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
	// while (i < argc - 3)
	// {
		
	// }
}

int main(int argc, char **argv, char **envp)
{
	t_path	path;
	
	if (argc < 4)
	{
		ft_putendl_fd("Error not enough args", 2);
		exit(EXIT_FAILURE);
	}
	path.path = get_path(envp, argv, argc);
	path.cmd = malloc(sizeof(char *) * (argc - 2));
	if (!path.cmd)
		show_error("Malloc failed");
	get_binary(&path, argc, argv);
	check_args(argc, argv, &path);
	printf("%s\n", path.cmd[0]);
	printf("%s\n", path.cmd[1]);
	printf("%s\n", path.cmd[2]);
	printf("%s\n", path.cmd[3]);
	printf("%s\n", path.cmd[4]);
	printf("%s\n", path.cmd[5]);
	return (0);
}
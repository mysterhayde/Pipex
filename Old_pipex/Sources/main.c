/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:07:38 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/16 16:20:17 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void check_arguments(int argc, char **argv, t_binary *binary)
{
	printf("%s\n", "check_args");
	int	i;

	i = 0;
	if (argc != 5)
	{
		if (argc > 5)
			show_errors(binary, TOO_MUCH_ARGS);
		else if (argc < 5)
			show_errors(binary, NOT_ENOUGH_ARGS);			
	}
	if (access(argv[1], R_OK) == -1)
		show_errors(binary, CANNOT_ACCES);
	if (access(argv[argc - 1], W_OK) == -1)
		show_errors(binary, CANNOT_ACCES);
	while (i < (argc - 3))
	{
		find_binary(binary, argv[i + 2]);
		printf("%s\n", binary->cmd[0]);
		i++;
	}
}

static void	init_binary(t_binary *binary, int argc)
{
	int	i;

	i = 0;
	binary->cmd = malloc(sizeof(char *) * (argc - 2));
	if (!binary->cmd)
		show_errors(binary, MALLOC_ERROR);
	while(i < (argc - 2))
	{
		binary->cmd[i] = NULL;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_binary	binary;

	init_binary(&binary, argc);
	check_arguments(argc, argv, &binary);
	clean_exit(&binary, EXIT_SUCCESS, argc);
	return (0);
}

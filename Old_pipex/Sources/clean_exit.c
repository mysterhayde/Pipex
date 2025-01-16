/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:03:07 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/16 16:15:22 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_exit(t_binary *binary, int exit_status, int argc)
{
	printf("%s\n", "clean_exit");
	int	i;
	
	i = 0;
	while(i < argc - 3)
	{
		printf("%s\n", binary->cmd[i]);
		free(binary->cmd[i]);
		i++;
	}
	free(binary->cmd);
	exit(exit_status);
}
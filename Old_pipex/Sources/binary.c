/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:56:47 by hdougoud          #+#    #+#             */
/*   Updated: 2025/01/16 16:07:10 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	convert_binary(t_binary *binary, char *bin)
{
	int	i;

	i = 0;
	if (!bin)
		show_errors(binary, MALLOC_ERROR);
	while (!binary->cmd[i])
		i++;
	binary->cmd[i] = ft_strdup(bin);
	free(bin);
	
	printf("final bin %s\n", binary->cmd[i]); //debug
}

void	find_binary(t_binary *binary, char *str)
{
	char	*bin;

	bin = ft_strjoin("/bin/", str);
	if ((access(bin, X_OK) >= 0))
	{
		convert_binary(binary, bin);
		return ;
	}
	safe_free((void **) &bin);
	bin = ft_strjoin("/usr/bin/", str);
	if ((access(bin, X_OK)) >= 0)
	{
		convert_binary(binary, bin);
		return ;
	}
	safe_free((void **) &bin);
	show_errors(binary, CANNOT_ACCES);
}

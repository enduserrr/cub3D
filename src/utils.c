/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:00:25 by asalo             #+#    #+#             */
/*   Updated: 2024/10/15 11:01:26 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*read_fd(int fd)
{
	int		flag;
	char	*str;
	char	*tmp;
	char	buffer[1085];

	str = NULL;
	flag = 1;
	while (flag)
	{
		flag = read(fd, buffer, 1084);
		buffer[flag] = 0;
		tmp = str;
		str = ft_strjoin(tmp, buffer);
	}
	return (str);
}

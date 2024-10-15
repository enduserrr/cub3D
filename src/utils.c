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

/*returns non zero for white space*/

int	validate_char(char c)
{
	if (ft_isspace(c) || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == '0' || c == '1' || c == '\0')
		return (1);
	return (0);
}

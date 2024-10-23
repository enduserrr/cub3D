/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:18:09 by asalo             #+#    #+#             */
/*   Updated: 2024/10/22 13:18:12 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

/*Change to put info into an array.*/
static int	parse_line(char *line, t_map *map_info)
{
	while (ft_isspace(*line))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		map_info->NO = line + 3;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		map_info->SO = line + 3;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		map_info->WE = line + 3;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		map_info->EA = line + 3;
	else if (ft_strncmp(line, "F ", 2) == 0)
		map_info->F = line + 2;
	else if (ft_strncmp(line, "C ", 2) == 0)
		map_info->C = line + 2;
    else
        return (1);
    return (0);
}

void	visual_info(t_map *map_info)
{
    int     i;
	int     k;
	char	**tmp;

	tmp = map_info->temp_map;
	k = 0;
	while (tmp[k])
	{
        if (parse_line(tmp[k], map_info))
            break ;
		k++;
	}
    i = 0;
	while (tmp[k])
	{
		tmp[i] = tmp[k];
		i++;
		k++;
	}
	tmp[i] = NULL;
	map_info->temp_map = tmp;
}


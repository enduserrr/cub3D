/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enclosure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:44:21 by asalo             #+#    #+#             */
/*   Updated: 2024/11/21 10:44:25 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

static void	restore(char **map, size_t size_y)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < size_y)
	{
		x = 0;
		printf("%s\n", map[y]);
		while (map[y][x])
		{
			if (map[y][x] == 'v')
				map[y][x] = '0';
			x++;
		}
		y++;
	}
}

static int	fill(char **map, size_t x, size_t y, size_t max_x, size_t max_y)
{
	if (x >= max_x || y >= max_y || x < 0 || y < 0 || map[y][x] == '\0')
		return (1);
	if (map[y][x] == '1' || map[y][x] == '0')
        return (0);
	if (map[y][x] != '0' && !is_player(map[y][x]))
		return (1);
	if (map[y][x] == '0')
		map[y][x] = 'v';
	fill(map, x + 1, y, max_x, max_y);
	fill(map, x - 1, y, max_x, max_y);
	fill(map, x, y + 1, max_x, max_y);
	fill(map, x, y - 1, max_x, max_y);
	if (map[y][x] == ' ')
		map[y][x] == '0';
	return (0);
}

int	wall_coverage(t_map *info)
{
	size_t	y;
	size_t	x;
	int		res;

	y = 1;
	while (y < (info->size_y - 1))
	{
		x = -1;
		while (++x < (ft_strplen(info->map[y]) - 1))
		{
			if (info->map[y][x] == '0')
			{
				res = fill(info->map, x, y, ft_strplen(info->map[y]), info->size_y);
				if (res == 1)
					return (1);
			}
			printf("%s\n", info->map[y]);
		}
		y++;
	}
	restore(info->map, info->size_y);
	return (0);
}


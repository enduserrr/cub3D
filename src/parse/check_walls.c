/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:44:21 by asalo             #+#    #+#             */
/*   Updated: 2024/11/23 11:24:11 by asalo            ###   ########.fr       */
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

static int	fill2(char **map, size_t x, size_t y, size_t xmax, size_t ymax)
{
	if (x >= xmax || y >= ymax || map[y][x] == '\0')
		return (1);
	if (map[y][x] == 'v' || map[y][x] == '1' || map[y][x] == ' ')
		return (0);
	if (map[y][x] == '2')
	{
		if ((y > 0 && map[y - 1][x] == '0') ||
			(y + 1 < ymax && map[y + 1][x] == '0') ||
			(x > 0 && map[y][x - 1] == '0') ||
			(x + 1 < xmax && map[y][x + 1] == '0'))
		{
			map[y][x] = '0';
			return (1);
		}
		map[y][x] = ' ';
	}
	fill2(map, x + 1, y, xmax, ymax);
	fill2(map, x - 1, y, xmax, ymax);
	fill2(map, x, y + 1, xmax, ymax);
	fill2(map, x, y - 1, xmax, ymax);
	return (0);
}

static int	fill(char **map, size_t x, size_t y, size_t xmax, size_t ymax)
{
	if (x >= xmax || y >= ymax || x < 0 || y < 0 || map[y][x] == '\0')
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'v')
		return (0);
	if (map[y][x] == '2')
		return (1);
	if (map[y][x] != '0' && !is_player(map[y][x]))
		return (1);
	if (map[y][x] == '0')
		map[y][x] = 'v';
	fill(map, x + 1, y, xmax, ymax);
	fill(map, x - 1, y, xmax, ymax);
	fill(map, x, y + 1, xmax, ymax);
	fill(map, x, y - 1, xmax, ymax);
	return (0);
}

static int	handle_spaces(t_map *data)
{
	size_t	y;
	size_t	x;
	size_t	xmax;

	y = 0;
	while (y < (data->size_y - 1))
	{
		x = -1;
		xmax = ft_strplen(data->map[y]);
		while (++x < (xmax - 1))
		{
			if (data->map[y][x] == '2')
			{
				if (fill2(data->map, x, y, xmax, data->size_y))
					return (1);
			}
		}
		y++;
	}
	return (0);
}

/**/
int	wall_check(t_map *data)
{
	size_t	y;
	size_t	x;
	size_t	xmax;

	if (handle_spaces(data))
		return (1);
	y = 1;
	while (y < (data->size_y - 1))
	{
		x = -1;
		xmax = ft_strplen(data->map[y]);
		while (++x < (xmax - 1))
		{
			if (data->map[y][x] == '0')
			{
				if (fill(data->map, x, y, xmax, data->size_y))
					return (1);
			}
		}
		y++;
	}
	restore(data->map, data->size_y);
	return (0);
}

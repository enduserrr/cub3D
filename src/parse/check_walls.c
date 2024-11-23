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
		while (map[y][x])
		{
			if (map[y][x] == 'v')
				map[y][x] = '0';
			else if (map[y][x] == '2')
				map[y][x] = ' ';
			x++;
		}
		y++;
	}
}

/**
 * @brief	Checks any potential 2's found in the map and what they are
 *			surrounded with.
 * @return
 */
static int	fill2(t_map *data, size_t x, size_t y, size_t xmax)
{
	size_t	ymax;

	ymax = data->size_y;
	if (x >= xmax || y >= ymax || data->map[y][x] == '\0')
		return (1);
	if (data->map[y][x] == 'v' || data->map[y][x] == '1' || data->map[y][x] == ' ')
		return (0);
	if (data->map[y][x] == '2')
	{
		if ((y > 0 && data->map[y - 1][x] == '0') ||
			(y + 1 < ymax && data->map[y + 1][x] == '0') ||
			(x > 0 && data->map[y][x - 1] == '0') ||
			(x + 1 < xmax && data->map[y][x + 1] == '0'))
		{
			data->map[y][x] = '0';
			return (1);
		}
		data->map[y][x] = ' ';
	}
	fill2(data, x + 1, y, xmax);
	fill2(data, x - 1, y, xmax);
	fill2(data, x, y + 1, xmax);
	fill2(data, x, y - 1, xmax);
	return (0);
}

int	fill(t_map *data, size_t x, size_t y, size_t xmax)
{
	size_t	ymax;

	ymax = data->size_y;
	if (x >= xmax || y >= ymax || x < 0 || y < 0 || data->map[y][x] == '\0')
		return (1);
	if (data->map[y][x] == '1' || data->map[y][x] == 'v')
		return (0);
	if (data->map[y][x] == '2' || data->map[y][x] == ' ')
		return (1);
	if (data->map[y][x] != '0' && !is_player(data->map[y][x]))
		return (1);
	if (data->map[y][x] == '0')
		data->map[y][x] = 'v';
	fill(data, x + 1, y, xmax);
	fill(data, x - 1, y, xmax);
	fill(data, x, y + 1, xmax);
	fill(data, x, y - 1, xmax);
	return (0);
}

static int	handle_spaces(t_map *data)
{
	size_t	y;
	size_t	x;
	size_t	xmax;

	y = 0;
	while (y < (data->size_y))
	{
		x = -1;
		xmax = ft_strplen(data->map[y]);
		while (++x < (xmax - 1))
		{
			if (data->map[y][x] == '2')
			{
				if (fill2(data, x, y, xmax))
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
		return (write_err(ERROR_WALLS), 1);
	y = 1;
	while (y < (data->size_y - 1))
	{
		x = -1;
		xmax = ft_strplen(data->map[y]);
		while (++x < (xmax - 1))
		{
			if (data->map[y][x] == '0')
			{
				if (fill(data, x, y, xmax))
					return (write_err(ERROR_WALLS), 1);
			}
		}
		y++;
	}
	restore(data->map, data->size_y);
	return (0);
}

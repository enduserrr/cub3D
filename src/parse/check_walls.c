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

/**
 * @brief	Restores the map to its original state by replacing 'v' with '0'
 *          and '2' with a space (' ').
 * @param	map    The 2D map array.
 * @param	size_y Number of rows in the map.
 */
void	restore(char **map, size_t size_y)
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
 * @brief	Checks for spaces and if they're found within the map
 *			area or outside of it.
 * @return	1 if spaces are incorrect position, 0 otherwise.
 */
static int	handle_spaces(t_map *data)
{
	size_t	y;
	size_t	x;
	size_t	x_max;

	y = 0;
	while (y < (data->size_y))
	{
		x = 0;
		x_max = ft_strplen(data->map[y]);
		while (x < (x_max - 1))
		{
			if (data->map[y][x] == '2')
			{
				if (fill2(data, x, y, x_max))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

/**
 * @brief	Wall validation on the map by checking both spaces
 *			and '0's to ensure they are enclosed by walls.
 * @return	1 if the map is invalid, 0 otherwise.
 */
int	wall_check(t_map *data)
{
	size_t	y;
	size_t	x;
	size_t	x_max;

	if (handle_spaces(data))
		return (write_err(ERROR_MAP), 1);
	y = 0;
	while (y < (data->size_y - 1))
	{
		x = 0;
		x_max = ft_strplen(data->map[y]);
		while (x < (x_max - 1))
		{
			if (data->map[y][x] == '0')
			{
				if (fill(data, x, y, x_max))
					return (write_err(ERROR_MAP), 1);
			}
			x++;
		}
		y++;
	}
	restore(data->map, data->size_y);
	return (0);
}

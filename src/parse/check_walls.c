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

int edge_rows(t_map *data, size_t x, size_t y)
{
    if (data->map[y][x] == '0' || data->map[y - 1][x] == '0'
		|| is_player(data->map[y][x]) || is_player(data->map[y - 1][x]))
            return (1);
    data->map[y][x] = ' ';
    return (0);
}

/**
 * @brief	Checks any potential '2's in the map and determines if they are
 *			surrounded by '0's. Updates '2' to '0' if inside the playable
 *			area, or restores it to a space (' ') if outside.
 * @return	1 if an invalid state is found, 0 otherwise.
 */
int	fill2(t_map *data, size_t x, size_t y, size_t x_max)
{
	size_t	y_max;

	y_max = data->size_y;
	if (x >= x_max || y >= y_max || data->map[y][x] == '\0')
		return (1);
	if (data->map[y][x] == 'v' || data->map[y][x] == '1'
		|| data->map[y][x] == ' ')
		return (0);
	if (data->map[y][x] == '2')
	{
		if (y == data->size_y - 1)
			return (edge_rows(data, x, y));
		if ((y > 0 && (data->map[y - 1][x] == '0' || is_player(data->map[y - 1][x]))) ||
			(y + 1 < y_max && (data->map[y + 1][x] == '0' || is_player(data->map[y + 1][x]))) ||
			(x > 0 && (data->map[y][x - 1] == '0' || is_player(data->map[y][x - 1]))) ||
			(x + 1 < x_max && (data->map[y][x + 1] == '0' || is_player(data->map[y][x + 1]))))
		{
			return (1);
		}
		data->map[y][x] = ' ';
	}
	return (0);
}

/**
 * @brief	Checks if a specific cell in the map and its neighbors are valid,
 *			marking visited '0's with 'v' for wall validation.
 * @return	1 if the map is invalid, 0 otherwise.
 */
int	fill(t_map *data, size_t x, size_t y, size_t x_max)
{
	size_t	y_max;

	y_max = data->size_y;
	if (x >= x_max || y >= y_max || x < 0 || y < 0 || data->map[y][x] == '\0')
		return (1);
	if (data->map[y][x] == '1' || data->map[y][x] == 'v')
		return (0);
	if (data->map[y][x] == '2')
		return (1);
	if (data->map[y][x] != '0' && !is_player(data->map[y][x]))
		return (1);
	if (data->map[y][x] == '0')
    {
        if (y == data->size_y - 1)
            return (edge_rows(data, x, y));
        if (x == 0 || x == (ft_strplen(data->map[y]) - 1)
            || y == 0 || y == (data->size_y - 1))
            return (1);
        data->map[y][x] = 'v';
    }
	fill(data, x + 1, y, x_max);
	fill(data, x - 1, y, x_max);
    fill(data, x, y + 1, x_max);
	fill(data, x, y - 1, x_max);
	return (0);
}

/**
 * @brief	Processes spaces ('2') in the map to determine if they are part
 *			of the playable area or outside.
 * @return	1 if spaces are improperly handled, 0 otherwise.
 */
int	handle_spaces(t_map *data)
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
 * @brief	Full wall validation on the map by checking both spaces
 *			and '0's to ensure they are enclosed by walls.
 * @return	1 if the map is invalid, 0 otherwise.
 */
int	wall_check(t_map *data)
{
	size_t	y;
	size_t	x;
	size_t	x_max;

	if (handle_spaces(data))
		return (write_err(ERROR_WALLS), 1);
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
					return (write_err(ERROR_WALLS), 1);
			}
            x++;
		}
		y++;
	}
	restore(data->map, data->size_y);
	return (0);
}

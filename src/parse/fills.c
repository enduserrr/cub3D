/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fills.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:23:02 by asalo             #+#    #+#             */
/*   Updated: 2024/12/05 09:45:41 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

static int	edge_rows(t_map *data, size_t x, size_t y)
{
	if (data->map[y][x] == '0' || data->map[y - 1][x] == '0'
		|| is_player(data->map[y][x]) || is_player(data->map[y - 1][x]))
		return (1);
	data->map[y][x] = ' ';
	return (0);
}

/**
 * @brief	Checks if any spaces are found inside the playable map area.
 * @return	1 for an error, 0 otherwise.
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
		if ((y > 0 && (data->map[y - 1][x] == '0' || is_player(data->map[y
						- 1][x]))) || (y + 1 < y_max && (data->map[y
					+ 1][x] == '0' || is_player(data->map[y + 1][x]))) || (x > 0
				&& (data->map[y][x - 1] == '0' || is_player(data->map[y][x
						- 1]))) || (x + 1 < x_max && (data->map[y][x + 1] == '0'
					|| is_player(data->map[y][x + 1]))))
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
	(void)x_max;//poista tama
	if (data->map[y][x] != '0' && !is_player(data->map[y][x]))
		return (1);
	if (data->map[y][x] == '0')
	{
		if (y == data->size_y - 1 || y == 0)
			return (1);
		if (ft_strplen(data->map[y - 1]) < ft_strplen(data->map[y]) && (data->map[y - 1][x] != '0' && !is_player(data->map[y - 1][x]) && data->map[y - 1][x] != '1' && data->map[y - 1][x] != 'v'))
			return (1);
		if (ft_strplen(data->map[y + 1]) < ft_strplen(data->map[y]) && (data->map[y + 1][x] != '0' && !is_player(data->map[y + 1][x]) && data->map[y + 1][x] != '1' && data->map[y + 1][x] != 'v'))
			return (1);
		if ((ft_strplen(data->map[y]) == x + 1) || (data->map[y][x + 1] != '0' && data->map[y][x + 1] != '1' && !is_player(data->map[y][x + 1]) && data->map[y][x + 1] != 'v'))
			return (1);
		if (x == 0 || (data->map[y][x - 1] != '0' && data->map[y][x - 1] != '1' && !is_player(data->map[y][x - 1]) && data->map[y][x - 1] != 'v'))
			return (1);
		else
			data->map[y][x] = 'v';
	}
	return (0);
}

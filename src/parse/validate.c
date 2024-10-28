/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 09:36:45 by asalo             #+#    #+#             */
/*   Updated: 2024/10/17 09:36:49 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

/**
 * @brief	Function to separate map and map info starting from the end of arr
 *			to locate the map. After map find N/W/S/E/F/C and their values and
 *			updating correspongind t_map variables.
 *
 *			Function to remove white spaces from map & check for errors in it
 *			and copy it to t_game.
 */

static int	compare_rows(size_t shorter, size_t longer, char *long_row)
{
	size_t	i;

	if (!long_row)
		return (1);
	i = shorter;
	while (i < longer)
	{
		if (long_row[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief	 Determines whether all viable map area is covered with walls (1's).
 */
static int	wall_coverage(t_map *map_info)
{
	size_t	k;
	size_t	below;
	size_t	current;
	size_t	above;

	k = 1;
	while (k < (map_info->size_y - 1))
	{
		below = ft_strlen(map_info->temp_map[k - 1]);
		current = ft_strlen(map_info->temp_map[k]);
		above = ft_strlen(map_info->temp_map[k + 1]);
		if (!map_info->temp_map[k] || !map_info->temp_map[k - 1] || !map_info->temp_map[k + 1])
			return (1);
		if (current > below && compare_rows(below, current, map_info->temp_map[k]))
			return (1);
		else if (current < below && compare_rows(current, below, map_info->temp_map[k - 1]))
			return (1);
		if (current > above && compare_rows(above, current, map_info->temp_map[k]))
			return (1);
		else if (current < above && compare_rows(current, above, map_info->temp_map[k + 1]))
			return (1);
		k++;
	}
	return (0);
}

/**
 * @brief	Ensures both the first and last row consists only of 1's.
 *			Call wall checker.
 */
static int	first_and_last_row(t_map *map_info)
{
	int	i;
	int	j;

	i = 0;
	while (map_info->temp_map[0][i])
	{
		if (map_info->temp_map[0][i] != '1')
			return (write_err("invalid first row"), 1);
		i++;
	}
	i = 0;
	j = map_info->size_y - 1;
	while (map_info->temp_map[j][i])
	{
		if (map_info->temp_map[j][i] != '1')
			return (write_err("invalid last row"), 1);
		i++;
	}
	if (wall_coverage(map_info))
		return (write_err("invalid map walls"), 1);
	return (0);
}

/**
 * @brief	Checks for invalid characters found in the map.
 *			Swaps spaces to 1's.
 *			(Meaby don't swap space's before the string starts.)
 */
static int validate_chars(char **s, t_map *map_info)
{
    size_t		i;
	int		k;

	k = -1;
	while (s[++k])
	{
		i = -1;
		while (s[k][++i])
		{
			if (!is_player(s[k][i]) && s[k][i] != ' ' && s[k][i] != '0' && s[k][i] != '1')
				return (1);
			if (is_player(s[k][i]))
			{
				map_info->start_orientation = s[k][i];
				map_info->start_position_x = i;
				map_info->start_position_y = k;
			}
				map_info->start_orientation = s[k][i];
			if (s[k][i] == ' ')
				s[k][i] = '1';
		}
		if (s[k][i - 1] != '1')
			return (write_err("incorrect map"), 1);
		if (i > map_info->size_x)
        	map_info->size_x = i;
		map_info->size_y++;
	}
	if (first_and_last_row(map_info))
		return (1);
	return (0);
}

/**
 * @brief	Init & alloc memory for a texture info struct.
 *			Calls the functions to get and check the data for the map &
 *			the textures
 */
int	process_map(t_map *map_info)
{
	static t_txtr  *txtr;
	int		i;

    txtr = malloc(sizeof(t_txtr));
    if (!txtr)
        return (write_err("failed memory allocation"), 1);
    txtr->info = malloc(6 * sizeof(char *));
    if (!txtr->info)
        return (free(txtr), write_err("failed memory allocation"), 1);
    i = -1;
    while (++i < 6)
	{
        txtr->info[i] = NULL;
	}
	if (get_info(map_info, txtr))
	{
		free_arr(txtr->info);
        free(txtr);
        return (1);
	}
	if (validate_chars(map_info->temp_map, map_info))
		return (free_arr(map_info->temp_map), free_arr(txtr->info), 1);
	return (gameplay(map_info, txtr));
}

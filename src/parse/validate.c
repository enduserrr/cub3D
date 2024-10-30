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
	size_t	x;

	if (!long_row)
		return (1);
	x = shorter;
	while (x < longer)
	{
		if (long_row[x] != '1')
			return (1);
		x++;
	}
	return (0);
}

/**
 * @brief	 Determines whether all viable map area is covered with walls (1's).
 */
static int	wall_coverage(t_map *map_info)
{
	size_t	y;
	size_t	below;
	size_t	current;
	size_t	above;

	y = 1;
	while (y < (map_info->size_y - 1))
	{
		below = ft_strlen(map_info->temp_map[y - 1]);
		current = ft_strlen(map_info->temp_map[y]);
		above = ft_strlen(map_info->temp_map[y + 1]);
		if (!map_info->temp_map[y] || !map_info->temp_map[y - 1] || !map_info->temp_map[y + 1])
			return (1);
		if (current > below && compare_rows(below, current, map_info->temp_map[y]))
			return (1);
		else if (current < below && compare_rows(current, below, map_info->temp_map[y - 1]))
			return (1);
		if (current > above && compare_rows(above, current, map_info->temp_map[y]))
			return (1);
		else if (current < above && compare_rows(current, above, map_info->temp_map[y + 1]))
			return (1);
		y++;
	}
	return (0);
}

/**
 * @brief	Ensures both the first and last row consists only of 1's.
 *			Call wall checker.
 */
static int	first_and_last_row(t_map *map_info)
{
	int	x;
	int	y;

	x = 0;
	while (map_info->temp_map[0][x])
	{
		if (map_info->temp_map[0][x] != '1')
			return (write_err("invalid first row"), 1);
		x++;
	}
	x = 0;
	y = map_info->size_y - 1;
	while (map_info->temp_map[y][x])
	{
		if (map_info->temp_map[y][x] != '1')
			return (write_err("invalid last row"), 1);
		x++;
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

static int validate_chars(char **s, t_game *game)
{
    size_t		x;
	size_t		y;

	y = -1;
	while (s[++y])
	{
		x = -1;
		while (s[y][++x])
		{
			if (!is_player(s[y][x]) && s[y][x] != ' ' && s[y][x] != '0' && s[y][x] != '1')
				return (1);
			if (is_player(s[y][x]))
				set_player(game, s[y][x], x, y);
			if (s[y][x] == ' ')
				s[y][x] = '1';
		}
		if (s[y][x - 1] != '1')
			return (write_err("incorrect map"), 1);
		game->map_info->size_y++;
	}
	if (first_and_last_row(game->map_info))
		return (1);
	return (0);
}

/**
 * @brief	Init & alloc memory for a texture info struct.
 *			Calls the functions to get and check the data for the map &
 *			the textures
 */
int	process_map(t_game *game)
{
	t_txtr		txtr;
	t_player	p;

	txtr = (t_txtr){0};
	p = (t_player){0};
	game->textures = &txtr;
	game->player = &p;
	if (get_info(game))
	{
		free_arr(game->textures->info);
        return (1);
	}
	if (validate_chars(game->map_info->temp_map, game))
		return (free_arr(game->map_info->temp_map), free_arr(game->textures->info), 1);
	// printf("%f %f %f\n", game->player->ppx, game->player->ppy, game->player->pa);
	if (gameplay(game))
		return (free_arr(game->textures->info), 1);
	return (0);
}

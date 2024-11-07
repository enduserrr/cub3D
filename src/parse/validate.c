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

static int	cmpr_rows(size_t shorter, size_t longer, char *long_row)
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
		Determines whether all viable map area is covered with walls (1's).
 */
static int	wall_coverage(t_map *info)
{
	size_t	y;
	size_t	below;
	size_t	curr;
	size_t	above;

	y = 1;
	while (y < (info->size_y - 1))
	{
		below = ft_strlen(info->map[y - 1]);
		curr = ft_strlen(info->map[y]);
		above = ft_strlen(info->map[y + 1]);
		if (!info->map[y] || !info->map[y - 1] || !info->map[y + 1])
			return (1);
		if (curr > below && cmpr_rows(below, curr, info->map[y]))
			return (1);
		else if (curr < below && cmpr_rows(curr, below, info->map[y - 1]))
			return (1);
		if (curr > above && cmpr_rows(above, curr, info->map[y]))
			return (1);
		else if (curr < above && cmpr_rows(curr, above, info->map[y + 1]))
			return (1);
		y++;
	}
	return (0);
}

/**
 * @brief	Ensures both the first and last row consists only of 1's.
 *			Call wall checker.
 */
static int	first_and_last_row(t_map *info)
{
	int	x;
	int	y;

	x = 0;
	if (!info->map || !info->map[0])
		return (write_err("invalid first row"), 1);
	while (info->map[0][x])
	{
		if (info->map[0][x] != '1')
			return (write_err("invalid first row"), 1);
		x++;
	}
	y = info->size_y - 1;
	if (y < 0 || !info->map[y])
		return (write_err("invalid last row"), 1);
	x = 0;
	while (info->map[y][x])
	{
		if (info->map[y][x] != '1')
			return (write_err("invalid last row"), 1);
		x++;
	}
	if (wall_coverage(info))
		return (write_err("invalid map walls"), 1);
	return (0);
}

/**
 * @brief	Checks for invalid characters found in the map.
 *			Swaps spaces to 1's.
 *			(Meaby don't swap space's before the string starts.)
 */
static int	validate_chars(char **s, t_game *game)
{
	size_t	x;
	size_t	y;

	y = -1;
	game->info->size_y = 0;
	while (s[++y])
	{
		x = -1;
		while (s[y][++x])
		{
			if (!is_player(s[y][x]) && s[y][x] != ' ' && s[y][x] != '0'
				&& s[y][x] != '1')
				return (1);
			if (is_player(s[y][x]))
				set_player(game, s[y][x], x, y);
			if (s[y][x] == ' ')
				s[y][x] = '1';
		}
		if (s[y][x - 1] != '1')
			return (write_err("incorrect map"), 1);
		game->info->size_y++;
	}
	if (first_and_last_row(game->info))
		return (1);
	return (0);
}

/**
 * @brief	Init & alloc memory for a texture info struct.
 *			Calls the functions to get and check the data for the map &
 *			the textures
 */
int	processinfo(t_game *game)
{
	t_txtr		txtr;
	t_player	p;

	txtr = (t_txtr){0};
	p = (t_player){0};
	game->textures = &txtr;
	game->player = &p;
	game->player->set = false;
	if (get_info(game))
	{
		return (1);
	}
	if (validate_chars(game->info->map, game))
		return (free_arr(game->info->map), 1);
	if (gameplay(game))
		return (1);
	return (0);
}

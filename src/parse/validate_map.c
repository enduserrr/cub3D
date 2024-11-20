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
 * @brief  Compares the len of two rows and checks if the longer row is
 *         filled with walls ('1') in the excess positions.
 * @param  shorter  The length of the shorter row.
 * @param  longer   The length of the longer row.
 * @param  long_row The longer row string to validate.
 * @return 1 if the longer row has non-wall characters in excess positions,
 *         0 otherwise.
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
 * @brief  Determines whether all valid map areas are enclosed by walls ('1').
 * @param  info  The map structure containing the map and its dimensions.
 * @return 1 if the map is not fully enclosed by walls, 0 otherwise.
 *
 * This function iterates through each row of the map, comparing it with
 * the rows above and below to ensure proper wall coverage. It uses the
 * `cmpr_rows` function to validate areas where row lengths differ.
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
 * @brief	Validates that the first and last rows of the map consist only of 1's.
 * @param	info  The map structure containing the map and its dimensions.
 * @return	1 for invalid first or last row, 0 otherwise.
 *
 * Checker to validate the first and last rows of the map and then rest by
 * calling `wall_coverage` function.
 */
static int	first_and_last_row(t_map *info)
{
	int	x;
	int	y;

	x = 0;
	if (!info->map || !info->map[0])
		return (write_err(ERROR_MAP), 1);
	while (info->map[0][x])
	{
		if (info->map[0][x] != '1')
			return (write_err(ERROR_MAP), 1);
		x++;
	}
	y = info->size_y - 1;
	if (y < 0 || !info->map[y])
		return (write_err(ERROR_MAP), 1);
	x = 0;
	while (info->map[y][x])
	{
		if (info->map[y][x] != '1')
			return (write_err(ERROR_MAP), 1);
		x++;
	}
	if (wall_coverage(info))
		return (write_err(ERROR_MAP), 1);
	return (0);
}

/**
 * @brief	Validates map characters and initialises the player's position.
 * @param	s     The map array containing rows of the map as strings.
 * @param	game  The game structure to store map dimensions and player info.
 * @return	1 for incorrect characters or map format,
 *			0 otherwise.
 *
 * This function checks that the map contains only valid characters:
 * '0', '1', ' ' 'N', 'S', 'E', 'W'. Replaces spaces with '1'
 * and sets the player's initial position using `set_player`.
 */
static int	validate_chars(char **s, t_game *game)
{
	size_t	x;
	size_t	y;

	y = -1;
	game->data->size_y = 0;
	while (s[++y])
	{
		x = -1;
		while (s[y][++x])
		{
			if (!is_player(s[y][x]) && s[y][x] != ' ' && s[y][x] != '0'
				&& s[y][x] != '1')
				return (write_err(ERROR_MAP_CHAR), 1);
			if (is_player(s[y][x]))
				set_player(game, s[y][x], x, y);
			if (s[y][x] == ' ')
				s[y][x] = '1';
		}
		if (s[y][x - 1] != '1')
			return (write_err(ERROR_MAP), 1);
		game->data->size_y++;
	}
	if (first_and_last_row(game->data))
		return (1);
	return (0);
}

/**
 * @brief  Processes map and texture information, initialises the game state,
 *         and validates the game map.
 * @param  game  The main game structure to store textures, player, and map info.
 * @return 1 if any validation or initialization fails, 0 otherwise.
 *
 * Initialises the textures and player structs, calls the proper functions to
 * get & validate game map and map info.
 */
int	process_data(t_game *game)
{
	t_txtr		txtr;
	t_player	p;

	txtr = (t_txtr){0};
	txtr_ptrs_init(&txtr);
	p = (t_player){0};
	game->textures = &txtr;
	game->player = &p;
	if (get_info(game) == 1)
	{
		return (write_err(ERROR_MAP_INFO), free_arr(game->data->map), 1);
	}
	if (!game->textures->n_txtr || !game->textures->s_txtr
		|| !game->textures->w_txtr || !game->textures->e_txtr
		|| !game->textures->c || !game->textures->f)
		return (write_err(ERROR_MAP_INFO), free_arr(game->data->map), 1);
	if (validate_chars(game->data->map, game))
		return (free_arr(game->data->map), 1);
	if (game->player->is_set < 1 || game->player->is_set > 1)
		return (write_err(ERROR_PLAYER), free_arr(game->data->map), 1);
	if (gameplay(game))
		return (1);
	return (0);
}

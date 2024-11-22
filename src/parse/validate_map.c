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
		if (info->map[0][x] != '1' && info->map[0][x] != ' ' && info->map[0][x] != '2')
			return (write_err(ERROR_MAP), 1);
		x++;
	}
	y = info->size_y - 1;
	if (y < 0 || !info->map[y])
		return (write_err(ERROR_MAP), 1);
	x = 0;
	while (info->map[y][x])
	{
		if (info->map[y][x] != '1' && info->map[y][x] != ' ' && info->map[y][x] != '2')
			return (write_err(ERROR_MAP), 1);
		x++;
	}
	if (wall_coverage(info))
		return (write_err(ERROR_MAP), 1);
	return (0);
}

/**
 * @brief	Validates map characters and initialises the player's position.
 * @param	s     The cmptr_rowsmap array containing rows of the map as strings.
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
	while (s[++y])
	{
		x = 0;
		while (s[y][x] == ' ')
			x++;
		if (s[y][x] != '1')
			return (write_err(ERROR_MAP), 1);
		while (s[y][x])
		{
			if (!is_player(s[y][x]) && s[y][x] != ' ' && s[y][x] != '0' && s[y][x] != '1')
				return (write_err(ERROR_MAP_CHAR), 1);
			if (is_player(s[y][x]))
				set_player(game, s[y][x], x, y);
			if (s[y][x] == ' ' && x != 0 && s[y][x - 1] == '0')
				s[y][x] = '0';
			else if (s[y][x] == ' ')
				s[y][x] = '2';
			x++;
		}
		game->data->size_y++;
	}
	return (first_and_last_row(game->data));
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
		|| !game->textures->c || game->textures->f->flag == true
		|| game->textures->c->flag == true)
		return (write_err(ERROR_MAP_INFO), free_arr(game->data->map), 1);
	if (validate_chars(game->data->map, game))
		return (free_arr(game->data->map), 1);
	if (game->player->is_set < 1 || game->player->is_set > 1)
		return (write_err(ERROR_PLAYER), free_arr(game->data->map), 1);
	if (gameplay(game))
		return (1);
	return (0);
}

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
 * @brief	Validates that the first and last rows of the map contain only
 *			valid characters ('1', ' ', '2') before performing a full wall
 *			check.
 * @return	1 if the first or last row is invalid, 0 otherwise.
 */
/*// int	first_and_last_row(t_map *data)
// {
// 	int	x;
// 	int	y;

// 	if (!data->map || !data->map[0])
// 		return (write_err(ERROR_MAP), 1);
// 	x = -1;
// 	while (data->map[0][++x])
// 	{
// 		if (data->map[0][x] != '1' && data->map[0][x] != ' '
// 			&& data->map[0][x] != '2')
// 			return (write_err(ERROR_MAP), 1);
// 	}
// 	y = data->size_y - 1;
// 	x = -1;
// 	while (data->map[y][++x])
// 	{
// 		if (data->map[y][x] != '1' && data->map[y][x] != ' '
// 			&& data->map[y][x] != '2')
// 			return (write_err(ERROR_MAP), 1);
// 	}
// 	if (wall_check(data))
// 		return (1);
// 	return (0);
// }*/


/**
 * @brief  Compares the len of two rows and checks if the longer row is
 *         filled with walls ('1') in the excess positions.
 * @param  shorter  The length of the shorter row.
 * @param  longer   The length of the longer row.
 * @param  long_row The longer row string to validate.
 * @return 1 if the longer row has non-wall characters in excess positions,
 *         0 otherwise.
 */
int	cmpr_rows(size_t shorter, size_t longer, char *long_row)
{
	size_t	x;

	if (!long_row)
		return (1);
	x = shorter;
	while (x < longer)
	{
		if (long_row[x] != '1' && long_row[x] != ' ' && long_row[x] != '2')
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
int	wall_coverage(t_map *data, int row, int i)
{
	size_t	curr;
	size_t	cmpr;

	curr = ft_strlen(data->map[row]);
	cmpr = ft_strlen(data->map[row + i]);
	if (!data->map[row])
		return (on_row(row), 1);
	if (curr < cmpr && cmpr_rows(curr, cmpr, data->map[row + i]))
		return (on_row(row), 1);
	if (curr > cmpr && cmpr_rows(cmpr, curr, data->map[row + 1]))
		return (on_row(row), 1);
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
int	first_and_last_row(t_map *data)
{
	int	x;
	int	y;

	x = 0;
	if (!data->map || !data->map[0])
		return (write_err("row_err0"), 1);
	if (wall_coverage(data, 0, 1) || wall_coverage(data, (int)data->size_y - 1, -1))
		return (write_err("re_err1"), 1);
	while (data->map[0][x])
	{
		if (data->map[0][x] == '0')
			return (write_err("row_err2"), 1);
		x++;
	}
	y = data->size_y - 1;
	if (y < 0 || !data->map[y])
		return (write_err("row_err3"), 1);
	x = 0;
	while (data->map[y][x])
	{
		if (data->map[y][x] == '0')
			return (write_err("row_err4"), 1);
		x++;
	}
	// if (wall_coverage(data))
	// 	return (write_err("row_err5"), 1);
	return (wall_check(data));
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
/*// int	validate_chars(char **s, t_game *game)
// {
// 	size_t	x;
// 	size_t	y;

// 	y = -1;
// 	game->data->size_y = 0;
// 	while (s[++y])
// 	{
// 		x = -1;
// 		while (s[y][++x])
// 		{
// 			if (!is_player(s[y][x]) && s[y][x] != ' ' && s[y][x] != '0'
// 				&& s[y][x] != '1')
// 				return (write_err(ERROR_MAP_CHAR), 1);
// 			if (is_player(s[y][x]))
// 				set_player(game, s[y][x], x, y);
// 			if (s[y][x] == ' ')
// 				s[y][x] = '1';
// 		}
// 		if (s[y][x - 1] != '1')
// 			return (write_err(ERROR_MAP), 1);
// 		printf("%s\n", s[y]);
// 		game->data->size_y++;
// 	}
// 	if (first_and_last_row(game->data))
// 		return (1);
// 	return (0);
// }*/

/**
 * @brief	Basic char validation for the map & player position initialisation.
 *			Also converts spaces (' ') into '2's for processing.
 * @return	1 if incorrect chars or invalid map, 0 otherwise.
 */
int	validate_chars(char **s, t_game *game)
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
			return (write_err(ERROR_MAP_CHAR), 1);
		while (s[y][x])
		{
			if ((x == 0 && s[y][x] == '0') || s[y][ft_strplen(s[y]) - 1] == '0')
				return (write_err(ERROR_MAP_CHAR), 1);
			if (!is_player(s[y][x]) && s[y][x] != ' ' && s[y][x] != '0'
				&& s[y][x] != '1')
				return (write_err(ERROR_MAP_CHAR), 1);
			if (is_player(s[y][x]))
				set_player(game, s[y][x], x, y);
			else if (s[y][x] == ' ')
				s[y][x] = '2';
			x++;
		}
		// on_row((int)y);
		game->data->size_y++;
	}
	return (first_and_last_row(game->data));
}

static void	txtr_ptrs_init(t_txtr *t)
{
	t->n_txtr = NULL;
	t->s_txtr = NULL;
	t->e_txtr = NULL;
	t->w_txtr = NULL;
	t->gun = NULL;
	t->n_txtr = NULL;
	t->s_txtr = NULL;
	t->e_txtr = NULL;
	t->w_txtr = NULL;
	t->dup = false;
}

/**
 * @brief  Processes map and texture information, initialises the game state,
 *         and validates the game map.
 * @param  game  The main game structure to store textures, player, and map info.
 * @return 1 if any validation or initialization fails, 0 otherwise.
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
	if (get_data(game) == 1)
		return (write_err(ERROR_MAP_INFO), out(game, NULL), 1);
	if (!game || !game->textures || !game->textures->n_txtr
		|| !game->textures->s_txtr || !game->textures->w_txtr
		|| !game->textures->e_txtr || game->textures->dup == true)
		return (out(game, ERROR_MISSING_TXTR), 1);
	if (!game->textures->c || !game->textures->f || is_256(game->textures))
		return (write_err(ERROR_COLOR), out(game, NULL), 1);
	if (validate_chars(game->data->map, game))
		return (out(game, NULL), 1);
	if (!game->player || game->player->is_set < 1 || game->player->is_set > 1)
		return (write_err(ERROR_PLAYER), out(game, NULL), 1);
	if (gameplay(game))
		return (1);
	return (0);
}

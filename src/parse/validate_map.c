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
int	first_and_last_row(t_map *data)
{
	int	x;
	int	y;

	if (!data->map || !data->map[0])
		return (write_err(ERROR_MAP), 1);
	x = -1;
	while (data->map[0][++x])
	{
		if (data->map[0][x] != '1' && data->map[0][x] != ' '
			&& data->map[0][x] != '2')
			return (write_err(ERROR_MAP), 1);
	}
	y = data->size_y - 1;
	x = -1;
	while (data->map[y][++x])
	{
		if (data->map[y][x] != '1' && data->map[y][x] != ' '
			&& data->map[y][x] != '2')
			return (write_err(ERROR_MAP), 1);
	}
	if (wall_check(data))
		return (1);
	return (0);
}

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
		while (s[y][x])
		{
			if (!is_player(s[y][x]) && s[y][x] != ' ' && s[y][x] != '0'
				&& s[y][x] != '1')
				return (write_err(ERROR_MAP_CHAR), 1);
			if (is_player(s[y][x]))
				set_player(game, s[y][x], x, y);
			else if (s[y][x] == ' ')
				s[y][x] = '2';
			x++;
		}
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
		|| !game->textures->e_txtr)
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

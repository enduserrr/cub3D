/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 09:36:45 by asalo             #+#    #+#             */
/*   Updated: 2024/10/17 09:36:49 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

/* DEBUG --> DELETE */
void print_map(char **s)
{
	int y = 0;

	while(s[y])
	{
		printf("%s\n", s[y]);
		y ++;
	}
	printf("\n");
}

int invalid_char(char c)
{
	if (c != ' ' && c != '0' && c != '1')
		return 1;
	return 0;
}

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
			if (is_player(s[y][x]))
			{
				set_player(game, s[y][x], x, y);
				s[y][x] = '0';
			}
			if (invalid_char(s[y][x]))
				return (write_err(ERROR_MAP_CHAR), 1);
			x ++;
		}
		game->data->size_y++;
	}
	if (game->player->is_set != 1)
		return (write_err(ERROR_PLAYER), 1);
	return (0);
}

int validate_map(char **s, t_game *game)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (validate_chars(s, game))
		return 1;
	
	print_map(s);
	x = (int)game->player->ppx;
	y = (int)game->player->ppy;
	if (invalid_player_pos(s, x, y))
		return (write_err(ERROR_PLAYER_POS), 1);
	flood_fill(s, x, y);
	print_map(s);

	if (check_paths(s))
		return (1);
	return (0);
}

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

	//From this point forward changes have been made
	if (validate_map(game->data->map, game))
		return (out(game, NULL), 1);
	//No more changes 

	if (gameplay(game))
		return (1);
	return (0);
}

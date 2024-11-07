/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:28:17 by eleppala          #+#    #+#             */
/*   Updated: 2024/11/07 11:28:20 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

void	set_direction(t_game *game, double pax, double pay)
{
	game->player->pax = pax;
	game->player->pay = pay;
}

void	set_planes(t_game *game, double plane_x, double plane_y)
{
	game->player->plane_x = plane_x;
	game->player->plane_y = plane_y;
}

void set_orientation(t_game *game, char c)
{
	if (c == 'N')
	{
		set_direction(game, 0.0, -1.0);
		set_planes(game, FOV, 0.0);
	}
	else if (c == 'S')
	{
		set_direction(game, 0.0, 1.0);
		set_planes(game, -FOV, 0.0);
	}
	else if (c == 'W')
	{
		set_direction(game, -1.0, 0.0);
		set_planes(game, 0.0, -FOV);
	}
	else if (c == 'E')
	{
		set_direction(game, 1.0, 0.0);
		set_planes(game, 0.0, FOV);
	}
}

void	set_player(t_game *game, char c, size_t x, size_t y)
{
	if (game->player->set == true)
	{
		printf("%s%s%s\n", ORANGE, "Found multiple player positions.", RES);
		game->info->map[y][x] = '0';
		return ;
	}
	game->player->ppx = (double)x + 0.3;
	game->player->ppy = (double)y + 0.3;
	set_orientation(game, c);
	game->player->set = true;
}
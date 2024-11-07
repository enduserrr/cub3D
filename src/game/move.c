/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:05:40 by asalo             #+#    #+#             */
/*   Updated: 2024/11/07 10:05:47 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

void	rotate(t_game *game, int dir)
{
	double	speed;
	double	olddir;
	double	oldplane;

	speed = 3.0 * game->mlx->delta_time;
	olddir = game->player->pax;
	oldplane = game->player->plane_x;
	game->player->pax = game->player->pax * cos(speed * dir) - game->player->pay
		* sin(speed * dir);
	game->player->pay = olddir * sin(speed * dir) + game->player->pay
		* cos(speed * dir);
	game->player->plane_x = game->player->plane_x * cos(speed * dir)
		- game->player->plane_y * sin(speed * dir);
	game->player->plane_y = oldplane * sin(speed * dir) + game->player->plane_y
		* cos(speed * dir);
}

void	move_up(t_game *game, double speed, double bumber)
{
	int	x;
	int	y;

	x = (int)(game->player->ppx + game->player->pax * (speed + bumber));
	y = (int)(game->player->ppy);
	if (game->info->map[y][x] != '1')
		game->player->ppx += game->player->pax * speed;
	x = (int)(game->player->ppx);
	y = (int)(game->player->ppy + game->player->pay * (speed + bumber));
	if (game->info->map[y][x] != '1')
		game->player->ppy += game->player->pay * speed;
}

void	move_down(t_game *game, double speed, double bumber)
{
	int	x;
	int	y;

	x = (int)(game->player->ppx - game->player->pax * (speed + bumber));
	y = (int)game->player->ppy;
	if (game->info->map[y][x] != '1')
		game->player->ppx -= game->player->pax * speed;
	x = (int)(game->player->ppx);
	y = (int)(game->player->ppy - game->player->pay * (speed + bumber));
	if (game->info->map[y][x] != '1')
		game->player->ppy -= game->player->pay * speed;
}

void	move_left(t_game *game, double speed, double bumber)
{
	int	x;
	int	y;

	x = (int)(game->player->ppx + game->player->pay * (speed + bumber));
	y = (int)(game->player->ppy);
	if (game->info->map[y][x] != '1')
		game->player->ppx += game->player->pay * speed;
	x = (int)(game->player->ppx);
	y = (int)(game->player->ppy - game->player->pax * (speed + bumber));
	if (game->info->map[y][x] != '1')
		game->player->ppy -= game->player->pax * speed;
}

void	move_right(t_game *game, double speed, double bumber)
{
	int	x;
	int	y;

	x = (int)(game->player->ppx - game->player->pay * (speed + bumber));
	y = (int)(game->player->ppy);
	if (game->info->map[y][x] != '1')
		game->player->ppx -= game->player->pay * speed;
	x = (int)(game->player->ppx);
	y = (int)(game->player->ppy + game->player->pax * (speed + bumber));
	if (game->info->map[y][x] != '1')
		game->player->ppy += game->player->pax * speed;
}

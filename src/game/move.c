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

/**
 * @brief 	Rotates the player's view direction and camera plane.
 * @param 	game 	The game structure containing the player's position and 
 * 					view direction.
 * @param 	dir 	The direction to rotate: -1 for counterclockwise, 1 for clockwise.
 * 
 * This function rotates the player's direction (`pax`, `pay`) and the camera 
 * plane (`plane_x`, `plane_y`) by a specified angle determined by the `dir` 
 * parameter. The rotation is applied based on the current speed, which is 
 * multiplied by the delta time (`game->mlx->delta_time`). The `cos` and `sin` 
 * functions are used tocompute the new direction and plane values after rotation.
 */

void	rotate(t_game *game, int dir)
{
	double	speed;
	double	co;
	double	si;
	double	dir_x;
	double	plane_x;

	speed = 3.0 * game->mlx->delta_time;
	co = cos(speed * dir);
	si = sin(speed * dir);
	dir_x = game->player->pax;
	plane_x = game->player->plane_x;
	game->player->pax = game->player->pax * co - game->player->pay * si;
	game->player->pay = dir_x * si + game->player->pay * co;
	game->player->plane_x = game->player->plane_x * co - game->player->plane_y
		* si;
	game->player->plane_y = plane_x * si + game->player->plane_y * co;
}

/**
 * @brief 	Moves the player forward in the direction they are facing.
 * @param 	game 	The game structure containing the player's position 
 * 					and direction.
 * @param 	speed 	The speed of the player's movement, based on the frame time.
 * @param 	bumber 	An additional factor used to adjust movement precision 
 * 					and collision detection.
 * 
 * This function moves the player forward by updating their `ppx` and `ppy` 
 * coordinates based on their direction (`pax` and `pay`). It first checks 
 * if the new position collides with a wall (represented by '1' in the map).
 * If there is no collision, the player is moved forward.
 */

void	move_up(t_game *game, double speed, double bumber)
{
	int	x;
	int	y;

	x = (int)(game->player->ppx + game->player->pax * bumber);
	y = (int)(game->player->ppy);
	if (game->info->map[y][x] != '1')
		game->player->ppx += game->player->pax * speed;
	x = (int)(game->player->ppx);
	y = (int)(game->player->ppy + game->player->pay * bumber);
	if (game->info->map[y][x] != '1')
		game->player->ppy += game->player->pay * speed;
}

/**
 * @brief 	Moves the player backwards in the direction they are facing.
 * @param 	game 	The game structure containing the player's position 
 * 					and direction.
 * @param 	speed 	The speed of the player's movement, based on the frame time.
 * @param 	bumber 	An additional factor used to adjust movement precision 
 * 					and collision detection.
 * 
 * This function moves the player backwars by updating their `ppx` and `ppy` 
 * coordinates based on their direction (`pax` and `pay`). It first checks 
 * if the new position collides with a wall (represented by '1' in the map).
 * If there is no collision, the player is moved backwards.
 */

void	move_down(t_game *game, double speed, double bumber)
{
	int	x;
	int	y;

	x = (int)(game->player->ppx - game->player->pax * bumber);
	y = (int)game->player->ppy;
	if (game->info->map[y][x] != '1')
		game->player->ppx -= game->player->pax * speed;
	x = (int)(game->player->ppx);
	y = (int)(game->player->ppy - game->player->pay * bumber);
	if (game->info->map[y][x] != '1')
		game->player->ppy -= game->player->pay * speed;
}

/**
 * @brief 	Moves the player sideways in the direction they are facing.
 * @param 	game 	The game structure containing the player's position 
 * 					and direction.
 * @param 	speed 	The speed of the player's movement, based on the frame time.
 * @param 	bumber 	An additional factor used to adjust movement precision 
 * 					and collision detection.
 * 
 * This function moves the player sideways by updating their `ppx` and `ppy` 
 * coordinates based on their direction (`pax` and `pay`). It first checks 
 * if the new position collides with a wall (represented by '1' in the map).
 * If there is no collision, the player is moved sideways.
 */

void	move_left(t_game *game, double speed, double bumber)
{
	int	x;
	int	y;

	x = (int)(game->player->ppx + game->player->pay * bumber);
	y = (int)(game->player->ppy);
	if (game->info->map[y][x] != '1')
		game->player->ppx += game->player->pay * speed;
	x = (int)(game->player->ppx);
	y = (int)(game->player->ppy - game->player->pax * bumber);
	if (game->info->map[y][x] != '1')
		game->player->ppy -= game->player->pax * speed;
}

/**
 * @brief 	Moves the player sideways in the direction they are facing.
 * @param 	game 	The game structure containing the player's position 
 * 					and direction.
 * @param 	speed 	The speed of the player's movement, based on the frame time.
 * @param 	bumber 	An additional factor used to adjust movement precision 
 * 					and collision detection.
 * 
 * This function moves the player sideways by updating their `ppx` and `ppy` 
 * coordinates based on their direction (`pax` and `pay`). It first checks 
 * if the new position collides with a wall (represented by '1' in the map).
 * If there is no collision, the player is moved sideways.
 */

void	move_right(t_game *game, double speed, double bumber)
{
	int	x;
	int	y;

	x = (int)(game->player->ppx - game->player->pay * bumber);
	y = (int)(game->player->ppy);
	if (game->info->map[y][x] != '1')
		game->player->ppx -= game->player->pay * speed;
	x = (int)(game->player->ppx);
	y = (int)(game->player->ppy + game->player->pax * bumber);
	if (game->info->map[y][x] != '1')
		game->player->ppy += game->player->pax * speed;
}

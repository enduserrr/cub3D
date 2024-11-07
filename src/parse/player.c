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

/**
 * @brief 	Sets the player's direction vector.
 * @param 	game 	The game structure containing the player's state.
 * @param 	pax 	The X component of the direction vector (player's movement direction).
 * @param 	pay 	The Y component of the direction vector (player's movement direction).
 * 
 * This function sets the player's direction vector (`pax`, `pay`), which 
 * represents the direction the player is facing. This vector is used for 
 * movement and raycasting in the game.
 */

void	set_direction(t_game *game, double pax, double pay)
{
	game->player->pax = pax;
	game->player->pay = pay;
}

/**
 * @brief 	Sets the player's camera plane vector.
 * @param 	game 	The game structure containing the player's state.
 * @param 	plane_x 	The X component of the camera plane vector.
 * @param 	plane_y 	The Y component of the camera plane vector.
 * 
 * This function sets the player's camera plane (`plane_x`, `plane_y`), which 
 * determines the field of view and is used for raycasting calculations to 
 * render the environment correctly.
 */

void	set_planes(t_game *game, double plane_x, double plane_y)
{
	game->player->plane_x = plane_x;
	game->player->plane_y = plane_y;
}

/**
 * @brief 	Sets the player's initial direction and camera plane based on orientation.
 * @param 	game 	The game structure containing the player's state.
 * @param 	c 	The orientation character: 'N' 'S' 'W' 'E'.
 * 
 * This function initializes the player's facing direction and camera plane 
 * based on the given orientation character (`c`). The player's direction 
 * vector (`pax`, `pay`) and camera plane (`plane_x`, `plane_y`) are set 
 * according to the four possible directions (North, South, West, East) with 
 * predefined field-of-view (`FOV`) values.
 */

void	set_orientation(t_game *game, char c)
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

/**
 * @brief 	Sets the player's initial position and orientation on the map.
 * @param 	game 	The game structure containing the player's state.
 * @param 	c 	The orientation character ('N', 'S', 'W', 'E') 
 * 				representing the player's initial direction.
 * @param 	x 	The X coordinate of the player's position on the map.
 * @param 	y 	The Y coordinate of the player's position on the map.
 * 
 * This function sets the player's starting position (`ppx`, `ppy`) on 
 * the map based on the given `x` and `y` coordinates, and the player's 
 * orientation (direction and camera plane) is set according to the 
 * `c` parameter. The function also checks for multiple player positions 
 * on the map, and reports an error if more than one is found.
 */

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

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
 * @param 	pax 	The X component of the direction vector (movement dir).
 * @param 	pay 	The Y component of the direction vector (movement dir).
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
 * @param	plane_x 	The X component of the camera plane vector.
 * @param	plane_y 	The Y component of the camera plane vector.
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
 * @brief	Sets the player's initial direction.
 * @param	c 	The orientation character: 'N' 'S' 'W' 'E'.
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

int	check_player(t_game *game, size_t x, size_t y)
{
	if (x == 0 || x == ft_strplen(game->data->map[y]) || y == 0
		|| y == game->data->size_y - 1)
		return (1);
	if (x >= ft_strplen(game->data->map[y + 1])
		|| x >= ft_strplen(game->data->map[y - 1]))
		return (1);
	if (game->data->map[y][x + 1] == '1' && game->data->map[y][x - 1] == '1'
		&& game->data->map[y + 1][x] == '1' && game->data->map[y - 1][x] == '1')
		return (1);
	return (0);
}

/**
 * @brief	Sets the player's initial position and orientation on the map.
 * @param	c The orientation character ('N', 'S', 'W', 'E')
 *			representing the player's initial direction.
 * @param	x The X coordinate of the player's position on the map.
 * @param	y The Y coordinate of the player's position on the map.
 */
void	set_player(t_game *game, char c, size_t x, size_t y)
{
	if (game->player->is_set >= 1)
	{
		game->player->is_set += 1;
		game->data->map[y][x] = '0';
		return ;
	}
	game->player->ppx = (double)x + 0.3;
	game->player->ppy = (double)y + 0.3;
	set_orientation(game, c);
	game->player->is_set += 1;
}

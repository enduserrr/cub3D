/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:40:37 by eleppala          #+#    #+#             */
/*   Updated: 2024/10/25 13:58:34 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

void	wasd(t_game *game)
{
	double	speed;
	double	bumber;

	speed = 3.0 * game->mlx->delta_time;
	bumber = 0.5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		move_up(game, speed, bumber);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		move_down(game, speed, bumber);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		move_right(game, speed, bumber);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		move_left(game, speed, bumber);
	}
}

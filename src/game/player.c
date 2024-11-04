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

void rotate(t_game *game)
{
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
        game->player->pa -= 0.05;
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
        game->player->pa += 0.05;
    if (game->player->pa > 2 * PI)
        game->player->pa = 0;
    if (game->player->pa < 0)
        game->player->pa = 2 * PI;
    game->player->pax = cos(game->player->pa);
    game->player->pay = sin(game->player->pa);
    game->player->plane_x = -game->player->pay * 0.66; // 60 fov
    game->player->plane_y = game->player->pax * 0.66;  // 60 fov
    printf("%f %f\n", game->player->plane_x, game->player->plane_y);
}

void move_up(t_game *game, int speed)
{
    int x;
    int y;

    x = (int)(game->player->ppx + game->player->pax * (speed * speed)) / TILE;
    y = (int)(game->player->ppy + game->player->pay * (speed * speed)) / TILE;
    if (game->map_info->temp_map[y][x] != '1')
        game->player->ppx += game->player->pax * speed;
    if (game->map_info->temp_map[y][x] != '1')
        game->player->ppy += game->player->pay * speed;
}

void move_down(t_game *game, int speed)
{
    int x;
    int y;

    x = (int)(game->player->ppx - game->player->pax * (speed * speed)) / TILE;
    y = (int)(game->player->ppy - game->player->pay * (speed * speed)) / TILE;
    if (game->map_info->temp_map[y][x] != '1')
        game->player->ppx -= game->player->pax * speed;
    if (game->map_info->temp_map[y][x] != '1')
        game->player->ppy -= game->player->pay * speed;
}

void move_left(t_game *game, int speed)
{
    int x;
    int y;

    x = (int)(game->player->ppx + game->player->pay * (speed * speed)) / TILE;
    y = (int)(game->player->ppy - game->player->pax * (speed * speed)) / TILE;
    if (game->map_info->temp_map[y][x] != '1')
        game->player->ppx += game->player->pay * speed;
    if (game->map_info->temp_map[y][x] != '1')
        game->player->ppy -= game->player->pax * speed;
}

void move_right(t_game *game, int speed)
{
    int x;
    int y;

    x = (int)(game->player->ppx - game->player->pay * (speed * speed)) / TILE;
    y = (int)(game->player->ppy + game->player->pax * (speed * speed)) / TILE;
    if (game->map_info->temp_map[y][x] != '1')
        game->player->ppx -= game->player->pay * speed;
    if (game->map_info->temp_map[y][x] != '1')
        game->player->ppy += game->player->pax * speed;
}

void wasd(t_game *game)
{
    int speed = 5;

    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
        move_up(game, speed);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
         move_down(game, speed);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
        move_right(game, speed);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
        move_left(game, speed);
    }
}


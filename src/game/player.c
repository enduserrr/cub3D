/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:40:37 by eleppala          #+#    #+#             */
/*   Updated: 2024/10/17 15:40:40 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

void draw_player(t_game *game)
{
    int size;

    size = 10;
    draw_tile(game, size, game->player->ppx, game->player->ppy);
}

void init_player(t_player *player)
{
    player->ppx = 130;
    player->ppy = 300;
    player->mppx = WIN_WIDTH / 2;
    player->mppy = WIN_HEIGHT / 2;
    player->pa = PI / 2;
}

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
}

void move(t_game *game, float x, float y)
{
    game->player->ppx = x;
    game->player->ppy = y;
}

void wasd(t_game *game)
{
    int speed = 5;
    int s = 10;
    float c_angle;
    float s_angle;

    c_angle = cos(game->player->pa);
    s_angle = sin(game->player->pa);
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
        if (!wall(game, game->player->ppx + c_angle * (speed * s), game->player->ppy + s_angle * (speed * s)))
            move(game, game->player->ppx + c_angle * speed, game->player->ppy + s_angle * speed);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
        if (!wall(game, game->player->ppx - c_angle *(speed *s), game->player->ppy - s_angle *(speed *s)))
            move(game, game->player->ppx - c_angle * speed, game->player->ppy - s_angle * speed);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
        if (!wall(game, game->player->ppx - s_angle * (speed *s), game->player->ppy + c_angle * (speed *s)))
            move(game, game->player->ppx - s_angle * speed, game->player->ppy + c_angle * speed);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
        if (!wall(game, game->player->ppx + s_angle * (speed *s), game->player->ppy - c_angle * (speed *s)))
            move(game, game->player->ppx + s_angle * speed, game->player->ppy - c_angle * speed);
    }
}

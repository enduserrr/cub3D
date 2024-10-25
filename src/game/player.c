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

void init_player(t_map *map_info, t_player *player)
{
    player->ppx = (float)map_info->start_position_x * 64;
    player->ppy = (float)map_info->start_position_y * 64;
    player->mppx = WIN_WIDTH / 2;
    player->mppy = WIN_HEIGHT / 2;
    // if (map_info->start_orientation == 'N')
    //     player->pa = PI / 2;
    // else if (map_info->start_orientation == 'S')
    //     player->pa = 3 * PI / 2;
    // else if (map_info->start_orientation == 'W')
    //     player->pa = PI;
    // else if (map_info->start_orientation == 'E')
    //     player->pa = 0;
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

void move(t_game *game, float new_x, float new_y)
{
    float old_x = game->player->ppx;
    float old_y = game->player->ppy;

    game->player->ppx = new_x;
    game->player->ppy = new_y;

    /*check for walls in the newest position*/
    if (wall(game, game->player->ppx * 1000, game->player->ppy * 1000))
    {
        /*if wall back to the lates position*/
        game->player->ppx = old_x;
        game->player->ppy = old_y;
    }
}


/*void move(t_game *game, float x, float y)
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
}*/

void wasd(t_game *game)
{
    float speed = 5.0f;
    float c_angle = cos(game->player->pa);
    float s_angle = sin(game->player->pa);

    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
    {
        move(game, game->player->ppx + c_angle * speed,
            game->player->ppy + s_angle * speed);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
    {
        move(game, game->player->ppx - c_angle * speed,
            game->player->ppy - s_angle * speed);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
    {
        move(game, game->player->ppx - s_angle * speed,
            game->player->ppy + c_angle * speed);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
    {
        move(game, game->player->ppx + s_angle * speed,
            game->player->ppy - c_angle * speed);
    }
}


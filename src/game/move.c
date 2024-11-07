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

void rotate(t_game *game, int dir)
{
    double speed = 3.0 * game->mlx->delta_time;
    double co;
    double si;
    double dir_x;
    double plane_x;

    co = cos(speed * dir);
    si = sin(speed * dir);
    dir_x = game->player->pax;
    plane_x = game->player->plane_x;
    game->player->pax = game->player->pax * co - game->player->pay * si;
    game->player->pay = dir_x * si + game->player->pay * co;
    game->player->plane_x = game->player->plane_x * co - game->player->plane_y * si;
    game->player->plane_y = plane_x * si + game->player->plane_y * co;
}

void move_up(t_game *game, double speed, double bumber)
{
    int x;
    int y;

    x = (int)(game->player->ppx + game->player->pax * bumber);
    y = (int)(game->player->ppy);
    if (game->info->map[y][x] != '1')
        game->player->ppx += game->player->pax * speed;
    x = (int)(game->player->ppx);
    y = (int)(game->player->ppy + game->player->pay * bumber);
    if (game->info->map[y][x] != '1')
        game->player->ppy += game->player->pay * speed;
}

void move_down(t_game *game, double speed, double bumber)
{
    int x;
    int y;

    x = (int)(game->player->ppx - game->player->pax * bumber);
    y = (int)game->player->ppy;
    if (game->info->map[y][x] != '1')
        game->player->ppx -= game->player->pax * speed;
    x = (int)(game->player->ppx);
    y = (int)(game->player->ppy - game->player->pay * bumber);
    if (game->info->map[y][x] != '1')
        game->player->ppy -= game->player->pay * speed;
}

void move_left(t_game *game, double speed, double bumber)
{
    int x;
    int y;

    x = (int)(game->player->ppx + game->player->pay * bumber);
    y = (int)(game->player->ppy);
    if (game->info->map[y][x] != '1')
        game->player->ppx += game->player->pay * speed;
    x = (int)(game->player->ppx);
    y = (int)(game->player->ppy - game->player->pax * bumber);
    if (game->info->map[y][x] != '1')
        game->player->ppy -= game->player->pax * speed;
}

void move_right(t_game *game, double speed, double bumber)
{
    int x;
    int y;

    x = (int)(game->player->ppx - game->player->pay * bumber);
    y = (int)(game->player->ppy);
    if (game->info->map[y][x] != '1')
        game->player->ppx -= game->player->pay * speed;
    x = (int)(game->player->ppx);
    y = (int)(game->player->ppy + game->player->pax * bumber);
    if (game->info->map[y][x] != '1')
        game->player->ppy += game->player->pax * speed;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:33:04 by eleppala          #+#    #+#             */
/*   Updated: 2024/10/17 16:33:07 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

void round_ray_hits(t_game *game, int i, float ray_x, float ray_y) 
{
    game->ray[i].hx = ray_x;
    game->ray[i].hy = ray_y;
    if (game->ray[i].hy % 64 == 1)
        game->ray[i].hy -= 1;
    if (game->ray[i].hy % 64 == 63)
        game->ray[i].hy += 1;
    if (game->ray[i].hx % 64 == 1)
        game->ray[i].hx -= 1;
    if (game->ray[i].hx % 64 == 63)
       game->ray[i].hx += 1;
}

void init_ray(t_game *game, int i, float ray_x, float ray_y, float angle)
{
    t_ray r;
    r = (t_ray){0};

    game->ray[i] = r;
    game->ray[i].corner = false;
    game->ray[i].index = i;
    game->ray[i].sx = ray_x;
    game->ray[i].sy = ray_y;
    game->ray[i].angle = angle;
}

void cast_ray(t_game *game, float ray_x, float ray_y, float angle, int i)
{
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);

    init_ray(game, i, ray_x, ray_y, angle);
    while(!wall(game, ray_x, ray_y))
    {
        mlx_put_pixel(game->screen, ray_x, ray_y, 0xFF16FF);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
    round_ray_hits(game, i, ray_x, ray_y);
    game->ray[i].length = ray_length(game, ray_x, ray_y);
    game->ray[i].wall_height = (TILE / game->ray[i].length) * (WIN_WIDTH / 2);
    game->ray[i].wall_y = (WIN_HEIGHT - game->ray[i].wall_height) / 2;
    hit_side(game, i);
}


void raycast(t_game *game)
{
    float ray_x = game->player->ppx;
    float ray_y = game->player->ppy;

    float a = game->player->pa - PI / 6;
    int i = 0;
    float fraction = PI / 3 / WIN_WIDTH;

    while (i < WIN_WIDTH)
    {
        //if (i == WIN_WIDTH / 2)
            cast_ray(game, ray_x, ray_y, a, i);
        a += fraction;
        i ++;
    }
}


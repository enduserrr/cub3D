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

void round_ray_hits(t_game *game)
{
    if (game->ray->hy % 64 != 0 && game->ray->hx % 64 != 0)
        game->ray->hy += 1;
    if (game->ray->hy % 64 != 0 && game->ray->hx % 64 != 0)
        game->ray->hy -= 2;
    if (game->ray->hx % 64 != 0)
        game->ray->hx += 1;
    if (game->ray->hx % 64 != 0)
        game->ray->hx -= 2;
}

void corner_case(t_game *game)
{
    if (game->ray->hx > game->player->ppx && game->ray->hy > game->player->ppy)
        game->ray->hs = 3;
    else if (game->ray->hx < game->player->ppx && game->ray->hy < game->player->ppy)
        game->ray->hs = 4;
    else if (game->ray->hx < game->player->ppx)
        game->ray->hs = 1;
    else
        game->ray->hs = 2;
}

void hit_side(t_game *game)
{
    round_ray_hits(game);
    if (game->ray->hy % 64 == 0 && game->ray->hx % 64 != 0)
    {
        if (game->ray->hy > game->player->ppy)
            game->ray->hs = 3;
        else
            game->ray->hs = 4;
    }
    else if (game->ray->hx % 64 == 0 && game->ray->hy % 64 != 0)
    {
        if (game->ray->hx > game->player->ppx)
            game->ray->hs = 2;
        else
            game->ray->hs = 1;
    }
    else
        corner_case(game);
}

void horizontal_rays(t_game *game, float ray_x, float ray_y, float a, int i)
{
    float height;
    float cos_angle = cos(a);
    float sin_angle = sin(a);

    game->ray->sx = ray_x;
    game->ray->sy = ray_y;
    while(!wall(game, ray_x, ray_y))
    {
        //mlx_put_pixel(game->screen, ray_x, ray_y, 0xFF16FF);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
    game->ray->hx = round(ray_x);
    game->ray->hy = round(ray_y);
    game->ray->length = ray_length(game, ray_x, ray_y);
    height = (TILE / game->ray->length) * (WIN_WIDTH / 2);
    //printf("ray_y: = %f ----", ray_y);
    ray_y = (WIN_HEIGHT - height) / 2;
    //printf("hy = %d\n, hx: %d -- ray_x = %f\n", game->ray->hy, game->ray->hx, ray_x);
    hit_side(game);
    draw_result(game, ray_y, height, i);
}


void raycast(t_game *game)
{
    float ray_x = game->player->ppx;
    float ray_y = game->player->ppy;

    float a = game->player->pa - PI / 6;
    float i = 0;
    float fraction = PI / 3 / WIN_WIDTH;

    while (i < WIN_WIDTH)
    {
        //if (i == WIN_WIDTH / 2)
            horizontal_rays(game, ray_x, ray_y, a, i);
        a += fraction;
        i ++;
    }
}

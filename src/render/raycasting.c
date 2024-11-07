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

void init_ray(t_game *game, int i)
{
    game->ray->camera_x = 2 * i / (double)WIN_WIDTH -1;
    game->ray->dir_x = game->player->pax + game->player->plane_x * game->ray->camera_x;
    game->ray->dir_y = game->player->pay + game->player->plane_y * game->ray->camera_x;
    game->ray->map_x = (int)game->player->ppx;
    game->ray->map_y = (int)game->player->ppy;
    if (game->ray->dir_x == 0)
        game->ray->d_dist_x = BIG_NUM;
    else
        game->ray->d_dist_x = fabs(1 / game->ray->dir_x);
    if (game->ray->dir_y == 0)
        game->ray->d_dist_y = BIG_NUM;
    else
        game->ray->d_dist_y = fabs(1 / game->ray->dir_y);
    game->ray->hit = 0;
}

void step(t_game *game)
{
    if (game->ray->dir_x < 0)
    {
        game->ray->step_x = -1;
        game->ray->s_dist_x = (game->player->ppx - (double)game->ray->map_x) * game->ray->d_dist_x;
    }
    else
    {
        game->ray->step_x = 1;
        game->ray->s_dist_x = ((double)(game->ray->map_x + 1.0) - game->player->ppx ) * game->ray->d_dist_x;
    }
    if (game->ray->dir_y < 0)
    {
        game->ray->step_y = -1;
        game->ray->s_dist_y = ((game->player->ppy - (double)game->ray->map_y)) * game->ray->d_dist_y;
    }
    else
    {
        game->ray->step_y = 1;
        game->ray->s_dist_y = (((double)game->ray->map_y + 1.0) - game->player->ppy ) * game->ray->d_dist_y;
    }
}

void dda(t_game *game)
{
    while(game->ray->hit == 0)
    {
        if (game->ray->s_dist_x < game->ray->s_dist_y)
        {
            game->ray->s_dist_x += game->ray->d_dist_x;
            game->ray->map_x += game->ray->step_x;
            game->ray->side = 0;
        }
        else
        {
            game->ray->s_dist_y += game->ray->d_dist_y;
            game->ray->map_y += game->ray->step_y;
            game->ray->side = 1;
        }
        if (game->map_info->map[game->ray->map_y][game->ray->map_x] == '1')
        {
            game->ray->hit = 1;
        }
    }
}

void walls(t_game *game)
{
    if (game->ray->side == 0)
        game->ray->distance = (game->ray->s_dist_x - game->ray->d_dist_x);
    else
        game->ray->distance = (game->ray->s_dist_y - game->ray->d_dist_y);
    game->ray->wall_height = (int)WIN_HEIGHT / game->ray->distance;
    game->ray->draw_start = WIN_HEIGHT / 2 - game->ray->wall_height / 2;
    if (game->ray->draw_start < 0)
        game->ray->draw_start = 0;
    game->ray->draw_end = WIN_HEIGHT / 2 + game->ray->wall_height / 2;
    if (game->ray->draw_end >= WIN_HEIGHT)
        game->ray->draw_end = WIN_HEIGHT - 1;
}

void raycast(t_game *game)
{
    t_ray r;
    r = (t_ray){0};
    int i;

    game->ray = &r;
    i = 0;
    while (i < WIN_WIDTH)
    {
        init_ray(game, i);
        step(game);
        dda(game);
        walls(game);
        draw(game, i);
        i ++;
    }
}


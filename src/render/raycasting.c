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

bool wall(t_game *game, int int_ray_x, int int_ray_y)
{
    int map_x;
    int map_y;

    map_x = (int_ray_x / 1000) / 64;
    map_y = (int_ray_y / 1000) / 64;
    if (game->map[map_y][map_x] == '1')
        return true;
    return false;
}


/*bool wall(t_game *game, float x, float y)
{
    int map_x;
    int map_y;

    map_x = x / 64;
    map_y = y / 64;
    if (game->map[map_y][map_x] == '1')
        return true;
    return false;
}*/

void draw_result(t_game *game, float ray_y, float height, int i)
{
    float wall;
    float sky;
    float floor;

    wall = ray_y + height;
    sky = ray_y + height;
    floor = ray_y + height;

    while(sky > 0)
    {
        pixel_safe(game, i, sky, 0x87CEEBFF);
        sky --;
    }
    while(ray_y < wall)
    {
        pixel_safe(game, i, ray_y, 0xB22222FF);
        ray_y ++;
    }

    while(floor < WIN_HEIGHT)
    {
        pixel_safe(game, i, floor, 0x008000FF);
        floor ++;
    }
}

float ray_length(t_game *game, float ray_x, float ray_y)
{
    float dx;
    float dy;
    float angle;
    float ray_length;

    dx = ray_x - game->player->ppx;
    dy = ray_y - game->player->ppy;
    ray_length = sqrt(dx * dx + dy * dy);
    angle = atan2(dy, dx) - game->player->pa;
    float length = ray_length * cos(angle);

    return (length);
}
void horizontal_rays(t_game *game, float ray_x, float ray_y, float a, int i)
{
    float height;
    float length;
    float cos_angle = cos(a);
    float sin_angle = sin(a);

    height = 0;

    int scaled_cos = (int)(cos_angle * 1000);/*scale up for precision*/
    int scaled_sin = (int)(sin_angle * 1000);
    int int_ray_x = (int)(ray_x * 1000);
    int int_ray_y = (int)(ray_y * 1000);

    while(!wall(game, int_ray_x, int_ray_y))
    {
        int_ray_x += scaled_cos;
        int_ray_y += scaled_sin;
    }
    /*back to float*/
    ray_x = int_ray_x / 1000.0f;
    ray_y = int_ray_y / 1000.0f;

    length = ray_length(game, ray_x, ray_y);
    height = (TILE / length) * (WIN_WIDTH / 2);
    ray_y = (WIN_HEIGHT - height) / 2;
    draw_result(game, ray_y, height, i);
}


/*void horizontal_rays(t_game *game, float ray_x, float ray_y, float a, int i)
{
    float height;
    float length;
    float cos_angle = cos(a);
    float sin_angle = sin(a);

    height = 0;
    while(!wall(game, ray_x, ray_y))
    {
        //mlx_put_pixel(game->screen, ray_x, ray_y, 0xFF16FF);
        ray_x += cos_angle;
        ray_y += sin_angle;
        //(void)i;
    }
    length = ray_length(game, ray_x, ray_y);
    height = (TILE / length) * (WIN_WIDTH / 2);
    ray_y = (WIN_HEIGHT - height) / 2;
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
        horizontal_rays(game, ray_x, ray_y, a, i);
        a += fraction;
        i ++;
    }
}*/

void raycast(t_game *game)
{
    float ray_x;
    float ray_y;
    float a;
    int i;
    float fraction;

    fraction = PI / 3 / WIN_WIDTH;
    a = game->player->pa - PI / 6;
    i = -1;
    while (++i < WIN_WIDTH)
    {
        ray_x = game->player->ppx;
        ray_y = game->player->ppy;
        horizontal_rays(game, ray_x, ray_y, a, i);
        a += fraction;
    }
}


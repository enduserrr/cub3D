/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 07:46:26 by asalo             #+#    #+#             */
/*   Updated: 2024/10/30 07:46:27 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"



void draw_tile(t_game *game, int size, int x, int y)
{
    int i = 0;

    while(i < size)
    {
        pixel_safe(game, x + i, y, 0xFF16FF);
        pixel_safe(game, x, y + i, 0xFF16FF);
        pixel_safe(game, x + i, y + size, 0xFF16FF);
        pixel_safe(game, x + size, y + i, 0xFF16FF);
        i ++;
    }
}

void draw_player(t_game *game)
{
    int size;

    size = 10;
    draw_tile(game, size, game->player->ppx, game->player->ppy);
}

void draw_wall(t_game *game, int wall, int i, float ray_y, float height)
{
    unsigned char   *pixels;
    unsigned int    color;
    float           texture_x;
    int             tex_x;
    float           step;
    float           texture_pos;

    step = 64 / height;
    texture_pos = 0.0;
    pixels = get_texture_pixels(game);
    if (game->ray->hs == 1 || game->ray->hs == 2)
        texture_x = fmod(game->ray->hy, TILE) / TILE;
    else
        texture_x = fmod(game->ray->hx, TILE) / TILE;
    tex_x = (int)(texture_x * 64);
    tex_x = tex_x % 64;
    while ((int)ray_y < (int)wall)
    {
        color = get_color(pixels, tex_x, texture_pos);
        pixel_safe(game, i, ray_y, color);
        texture_pos += step;
        ray_y++;
    }
}

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
    draw_wall(game, wall, i, ray_y, height);
    while(floor < WIN_HEIGHT)
    {
        pixel_safe(game, i, floor, 0x008000FF);
        floor ++;
    }
}



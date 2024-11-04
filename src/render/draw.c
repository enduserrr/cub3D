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

void draw_wall(t_game *game, int wall, int i)
{
    unsigned char   *pixels;
    unsigned int    color;
    float           texture_x;
    int             tex_x;
    float           step;
    float           texture_pos;

    step = TXTR_SIZE / game->ray[i].wall_height;
    texture_pos = 0.0;
    pixels = get_texture_pixels(game, i);
    if (game->ray[i].hs == 1 || game->ray[i].hs == 2) 
        texture_x = (fmodf(game->ray[i].hy, TILE) / TILE) * TXTR_SIZE;
    else
        texture_x = (fmodf(game->ray[i].hx, TILE) / TILE) * TXTR_SIZE;
    tex_x = (int)(texture_x)  % TXTR_SIZE;
    while ((int)game->ray[i].wall_y < (int)wall)
    {
        if ((int)texture_pos >= TXTR_SIZE) 
            break ;
        color = get_color(pixels, tex_x, (int)texture_pos);
        pixel_safe(game, i, game->ray[i].wall_y, color);
        texture_pos += step;
        game->ray[i].wall_y ++;
    }
}

void draw_result(t_game *game, int i)
{
    float wall;
    float sky;
    float floor;

    wall = game->ray[i].wall_y + game->ray[i].wall_height;
    sky = game->ray[i].wall_y + game->ray[i].wall_height;
    floor = game->ray[i].wall_y + game->ray[i].wall_height;
    while(sky > 0)
    {
        pixel_safe(game, i, sky, 0x87CEEBFF);
        sky --;
    }
    draw_wall(game, wall, i);
    while(floor < WIN_HEIGHT)
    {
        pixel_safe(game, i, floor, 0x008000FF);
        floor ++;
    }
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:27:11 by eleppala          #+#    #+#             */
/*   Updated: 2024/10/30 07:48:07 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

unsigned char *get_texture_pixels(t_game *game, int i) //
{
    if (game->ray[i].hs == 1)
        return game->textures->e_txtr->pixels;
    if (game->ray[i].hs == 2)
        return game->textures->w_txtr->pixels;
    if (game->ray[i].hs == 3)
        return game->textures->s_txtr->pixels;
    else
        return game->textures->n_txtr->pixels;
}

float ray_length(t_game *game, float ray_x, float ray_y) //
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

bool wall(t_game *game, float x, float y) //
{
    int map_x;
    int map_y;

    map_x = x / 64;
    map_y = y / 64;

    if (game->map_info->temp_map[map_y][map_x] == '1')
        return true;
    return false;
}

void pixel_safe(t_game *game, int x, float y, unsigned int color)
{
    if(x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
        return ;
    mlx_put_pixel(game->screen, x, (int)y, color);
}

unsigned int get_color(unsigned char *pixels, int tex_x, float texture_pos) // 
{
    int tex_y = (int)texture_pos;
    unsigned char *color_data;

    tex_y = tex_y % 64;
    color_data = pixels + (tex_y * 64 + tex_x) * 4;
    return (color_data[0] << 24) | (color_data[1] << 16) | (color_data[2] << 8) | color_data[3];
}





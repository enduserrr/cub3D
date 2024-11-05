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

void pixel_safe(t_game *game, int x, int y, uint32_t color)
{
    if(x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
        return ;
    mlx_put_pixel(game->screen, x, y, color);
}

static uint32_t rgb_to_hex(t_color *color)
{
    int red;
    int green;
    int blue;
    int a;

    if (!color || color->r > 255 || color->g > 255 || color->b > 255)
        return (0);
    red = (int)color->r;
    green = (int)color->g;
    blue = (int)color->b;
    a = (int)color->a;
    return ((a << 24) | (red << 16) | (green << 8) | blue);
}

void textures(t_game *game)
{
    if (game->ray->side == 0)
    {
        if (game->ray->map_x > game->player->ppx)
            game->ray->pixels = get_texture_pixels(game, 1); 
        else
            game->ray->pixels = get_texture_pixels(game, 2);
        game->ray->wall_x = game->player->ppy + game->ray->distance * game->ray->dir_y;
    }
    else if (game->ray->side == 1)
    {
        if (game->ray->map_y > game->player->ppy)
            game->ray->pixels = get_texture_pixels(game, 3); 
        else
            game->ray->pixels = get_texture_pixels(game, 4);
        game->ray->wall_x = game->player->ppx + game->ray->distance * game->ray->dir_x;
    }
    game->ray->wall_x -= floor(game->ray->wall_x);
    game->ray->text_x = (int)(game->ray->wall_x * (float)TXTR_SIZE);
    if (game->ray->side == 0 && game->ray->dir_x > 0)
        game->ray->text_x = TXTR_SIZE - game->ray->text_x - 1;
    if (game->ray->side == 1 && game->ray->dir_y < 0)
        game->ray->text_x = TXTR_SIZE - game->ray->text_x - 1;
}

void background(t_game *game, int i)
{
    int half;
    int start;
    uint32_t up;
    uint32_t down;

    up = rgb_to_hex(game->textures->f);
    down = rgb_to_hex(game->textures->c);
    half = WIN_HEIGHT / 2;
    start = 0;
    while (start < half)
    {
        pixel_safe(game, i, start, up);
        start ++;
    }
    while (start < WIN_WIDTH)
    {
        pixel_safe(game, i, start, up);
        start ++;
    }
}

void draw(t_game *game, int i)
{
	int		y;
	double	step;
	double	texture_pos;
    unsigned int color;

	y = game->ray->draw_start;
    int x = game->ray->draw_end;
	step = 1.0 * ((double)TXTR_SIZE) / (double)game->ray->wall_height;
	texture_pos = ((double)game->ray->draw_start - ((double)WIN_HEIGHT / 2.0) 
    + ((double)game->ray->wall_height / 2.0)) * step;
	textures(game);
    background(game, i);
    while (y < x)
	{
        game->ray->text_y = (int)texture_pos & (TXTR_SIZE - 1);
		texture_pos += step;
        color = get_color(game->ray->pixels, game->ray->text_x, game->ray->text_y);
		pixel_safe(game, i, y, (uint32_t)color);
		y++;
	}
}

// void draw_wall(t_game *game, int wall, int i)
// {
//     unsigned char   *pixels;
//     unsigned int    color;
//     float           texture_x;
//     int             tex_x;
//     float           step;
//     float           texture_pos;

//     step = TXTR_SIZE / game->ray[i].wall_height;
//     texture_pos = 0.0;
//     pixels = get_texture_pixels(game, i);
//     if (game->ray[i].hs == 1 || game->ray[i].hs == 2)
//         texture_x = (fmodf(game->ray[i].hy, TILE) / TILE) * TXTR_SIZE;
//     else
//         texture_x = (fmodf(game->ray[i].hx, TILE) / TILE) * TXTR_SIZE;
//     tex_x = (int)(texture_x)  % TXTR_SIZE;
//     while ((int)game->ray[i].wall_y < (int)wall)
//     {
//         if ((int)texture_pos >= TXTR_SIZE)
//             break ;
//         color = get_color(pixels, tex_x, (int)texture_pos);
//         pixel_safe(game, i, game->ray[i].wall_y, (uint32_t)color);
//         texture_pos += step;
//         game->ray[i].wall_y ++;
//     }
// }

// void draw_result(t_game *game, int i)
// {
//     float wall;
//     float sky;
//     float floor;
//     uint32_t    up;
//     uint32_t    down;

//     up = rgb_to_hex(game->textures->f);
//     down = rgb_to_hex(game->textures->c);
//     // printf("%x\n%x\n", up, down);
//     wall = game->ray[i].wall_y + game->ray[i].wall_height;
//     sky = game->ray[i].wall_y + game->ray[i].wall_height;
//     floor = game->ray[i].wall_y + game->ray[i].wall_height;
//     while(sky > 0)
//     {
//         pixel_safe(game, i, sky, up);/*0x87CEEBFF*/
//         sky --;
//     }
//     draw_wall(game, wall, i);
//     while(floor < WIN_HEIGHT)
//     {
//         pixel_safe(game, i, floor, down);/*0x008000FF*/
//         floor ++;
//     }
// }



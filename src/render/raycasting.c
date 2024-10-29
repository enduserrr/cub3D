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

bool wall(t_game *game, float x, float y)
{
    int map_x;
    int map_y;

    map_x = x / 64;
    map_y = y / 64;

    if (game->map_info->temp_map[map_y][map_x] == '1')
        return true;
    return false;
}

// bool wall(t_game *game, int int_ray_x, int int_ray_y)
// {
//     int map_x;
//     int map_y;

//     map_x = (int_ray_x / 1000) / 64;
//     map_y = (int_ray_y / 1000) / 64;
//     if (game->map[map_y][map_x] == '1')
//         return true;
//     return false;
// }

unsigned char *get_texture_pixels(t_game *game)
{
    if (game->ray->hs == 1)
        return game->textures->e_txtr->pixels;
    if (game->ray->hs == 2)
        return game->textures->w_txtr->pixels;
    if (game->ray->hs == 3)
        return game->textures->s_txtr->pixels;
    else
        return game->textures->n_txtr->pixels;
}

unsigned int get_color(unsigned char *pixels, int tex_x, float texture_pos)
{
    int tex_y = (int)texture_pos;
    unsigned char *color_data;

    tex_y = tex_y % 64;
    color_data = pixels + (tex_y * 64 + tex_x) * 4;
    return (color_data[0] << 24) | (color_data[1] << 16) | (color_data[2] << 8) | color_data[3];
}

void draw_wall(t_game *game, int wall, int i, float ray_y, float height)
{
    //magic number 64 on tassa tapauksessa texturen koko, fixaan myohemmin jonkun jarkevan

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

void round_ray_hits(t_game *game)
{
    //fixaa pyoristys virheet etta wall side detection oisi mahdollinen (ei vaikuta muihin laskelmiin)

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
    //tahan pitaa varmaan liittaa pelaajan angle suhteessa rayn angleen jotenkin
    //ei muuten toimi properly

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

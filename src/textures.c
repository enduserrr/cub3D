/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:06:42 by eleppala          #+#    #+#             */
/*   Updated: 2024/10/18 15:06:44 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
unsigned int get_texture_pixel(mlx_image_t *texture, int x, int y)
{
    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
        return 0; // Out of bounds
    return *((unsigned int *)(texture->pixels + (y * texture->width + x) * 4));
}*/

void load_textures(t_texture *test)
{
    test->n_txtr = mlx_load_png("/home/eleppala/Documents/projects/cubed/textures/north.png");
    if (!test->n_txtr)
        exit(12);
    test->e_txtr = mlx_load_png("/home/eleppala/Documents/projects/cubed/textures/east.png");
    if (!test->e_txtr)
        exit(12);
    test->s_txtr = mlx_load_png("/home/eleppala/Documents/projects/cubed/textures/south.png");
    if (!test->s_txtr)
        exit(12);
    test->w_txtr = mlx_load_png("/home/eleppala/Documents/projects/cubed/textures/west.png");
    if (!test->w_txtr)
        exit(12);
}


/*
void draw_result(t_game *game, float ray_y, float height, int i, float texture_x)
{
    float wall_bottom = ray_y + height; // Bottom of the wall slice
    int tex_x = (int)(texture_x * game->textures->n_txtr->width) % game->textures->n_txtr->width; // Ensure tex_x is within bounds

    unsigned int color;
    float step = (float)game->textures->n_txtr->height / height; // Calculate how much to move down the texture for each pixel
    float texture_pos = 0.0; // Start position in the texture for the top of the wall
    int y = (int)ray_y;

    while (ray_y > 0)
    {
        pixel_safe(game, i, (int)ray_y, 0x87CEEBFF);
        ray_y--;
    }

    // Draw the wall
    while (y < (int)wall_bottom)
    {
        int tex_y = (int)texture_pos % game->textures->n_txtr->height; // Ensure tex_y is within bounds

        // Fetch the color from the texture
        unsigned char *pixels = game->textures->n_txtr->pixels; // Get the pixel data from the texture
        int index = (tex_y * game->textures->n_txtr->width + tex_x) * 4; // Calculate the index for RGBA format
        color = (pixels[index] << 24) | (pixels[index + 1] << 16) | (pixels[index + 2] << 8) | pixels[index + 3];

        pixel_safe(game, i, y, color);

        texture_pos += step; // Move down the texture for the next pixel
        y++;
    }
    while (y < WIN_HEIGHT)
    {
        pixel_safe(game, i, y, 0x008000FF);
        y++;
    }
}*/
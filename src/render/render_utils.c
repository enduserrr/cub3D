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

unsigned char *get_texture_pixels(t_game *game, int i)
{
    if (i == 1)
        return game->textures->n_txtr->pixels;
    if (i == 2)
        return game->textures->s_txtr->pixels;
    if (i == 3)
        return game->textures->e_txtr->pixels;
    else
        return game->textures->w_txtr->pixels;
}

unsigned int get_color(unsigned char *pixels, int text_x, int text_y)
{
    int tex_y = text_y % TXTR_SIZE;
    int tex_x = text_x % TXTR_SIZE;
    unsigned char *color_data;

    tex_y = tex_y % 64;
    color_data = pixels + (tex_y * TXTR_SIZE + tex_x) * BYTES_P;
    return (color_data[0] << 24) | (color_data[1] << 16) | (color_data[2] << 8) | color_data[3];
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:27:11 by eleppala          #+#    #+#             */
/*   Updated: 2024/10/17 16:27:12 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

void pixel_safe(t_game *game, int x, float y, unsigned int color)
{
    if(x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
        return;
    mlx_put_pixel(game->screen, x, (int)y, color);
}

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

void draw_map(t_game *game)
{
    int x = (int)game->player->ppx / TILE;
    int y = (int)game->player->ppy / TILE;
    int i = 0;
    //int j = 0;

    while (game->map[y])
    {
        while(game->map[y][x])
        {

            if (game->map[y][x] == '1')
                draw_tile(game, TILE, x * TILE, y * TILE);
            x ++;
        }
        x = 0;
        y ++;
        i ++;
        if (i > 4)
            break ;
    }

    x = (int)game->player->ppx / TILE;
    y = (int)game->player->ppy / TILE;
    i = 0;
    while (game->map[y])
    {
        while(game->map[y][x])
        {

            if (game->map[y][x] == '1')
                draw_tile(game, TILE, x * TILE, y * TILE);
            x ++;
        }
        x = 0;
        y --;
        i ++;
        if (i > 4)
            break;
    }
}

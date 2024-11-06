/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:08:13 by eleppala          #+#    #+#             */
/*   Updated: 2024/11/06 14:08:15 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

void    delete_textures(t_game *game)
{
    if (game->textures->gun)
        mlx_delete_texture(game->textures->gun);
    if (game->textures->n_txtr)
        mlx_delete_texture(game->textures->n_txtr);
    if (game->textures->s_txtr)
        mlx_delete_texture(game->textures->s_txtr);
    if (game->textures->w_txtr)
        mlx_delete_texture(game->textures->w_txtr);
    if (game->textures->e_txtr)
        mlx_delete_texture(game->textures->e_txtr);
}

void    delete_images(t_game *game)
{
    if (game->gun)
    {
        mlx_delete_image(game->mlx, game->screen);
        //mlx_close_window(game->mlx);
    }
    if (game->screen)
    {
        mlx_delete_image(game->mlx, game->screen);
        mlx_close_window(game->mlx);
    }
}

void    out(t_game *game)
{
    delete_textures(game);
    delete_images(game); 
    mlx_terminate(game->mlx);
    free(game->textures->f);
    game->textures->f = NULL;
    free(game->textures->c);
    game->textures->c = NULL;
    free_map(game);
    game->map_info = NULL;
    game->mlx = NULL;
    game->textures = NULL;
    game->screen = NULL;
    game = NULL;
}
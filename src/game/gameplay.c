/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:03:36 by eleppala          #+#    #+#             */
/*   Updated: 2024/10/25 13:58:20 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

void screen(void *param)
{
    t_game *game;

    game = param;
    if (game->screen)
        mlx_delete_image(game->mlx, game->screen);
    if (!(game->screen = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT)))
	{
		mlx_close_window(game->mlx);
		exit(1);
	}
	if (mlx_image_to_window(game->mlx, game->screen, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		exit(1);
	}
    raycast(game);
}

void keys(void  *param)
{
	t_game *game;

    game = param;
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
    wasd(game);
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
        rotate(game, -1);
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
        rotate(game, 1);
}
void    out(t_game *game)
{
    mlx_delete_texture(game->textures->n_txtr);
    mlx_delete_texture(game->textures->s_txtr);
    mlx_delete_texture(game->textures->w_txtr);
    mlx_delete_texture(game->textures->e_txtr);
    if (game->screen)
    {
        mlx_delete_image(game->mlx, game->screen);
        mlx_close_window(game->mlx);
    }
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

int gameplay(t_game *game)
{
    if (!(game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, true)))
        exit(1);
    mlx_loop_hook(game->mlx, screen, game);
    mlx_loop_hook(game->mlx, keys, game);
	mlx_loop(game->mlx);
    out(game);
    return (0);
}

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

void render(t_game *game)
{
    int i;

    i = 0;
    while (i < WIN_WIDTH)
    {
        draw_result(game, i);
        i ++;
    }
}

void screen(t_game *game)
{
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
    render(game);
}

void keys(void  *param)
{
	t_game *game;

    game = param;
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
    wasd(game);
    rotate(game);
    screen(game);
}

int gameplay(t_game *game)
{
    if (!(game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, true)))
        exit(1);
    screen(game);
    mlx_loop_hook(game->mlx, keys, game);
	mlx_loop(game->mlx);
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
    free_map(game);
    game->map_info = NULL;
    game->mlx = NULL;
    game->textures = NULL;
    game->screen = NULL;
    game = NULL;
    return (0);
}

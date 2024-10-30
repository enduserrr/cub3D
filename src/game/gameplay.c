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

// void load_textures(t_txtr *txtr)
// {
//     txtr->n_txtr = mlx_load_png(txtr->info[0]);
//     if (!txtr->n_txtr)
//         exit(12);
//     txtr->s_txtr = mlx_load_png(txtr->info[1]);
//     if (!txtr->s_txtr)
//         exit(12);
//     txtr->w_txtr = mlx_load_png(txtr->info[2]);
//     if (!txtr->w_txtr)
//         exit(12);
//     txtr->e_txtr = mlx_load_png(txtr->info[3]);
//     if (!txtr->e_txtr)
//         exit(12);
// }

int gameplay(t_game *game)
{
    if (!(game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, true)))
        exit(1);
    // load_textures(game->textures);
    screen(game);
    mlx_loop_hook(game->mlx, keys, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);/*tilalle exit loop joka putsaa structit ja sulkee pelin?*/
    return (0);
}

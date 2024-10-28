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

    //for debugging or minimap..
    //draw_map(game);
    //draw_player(game);
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

void init_game(t_game *game, t_player *player, t_txtr *txtr, t_ray *r)
{
    if (!(game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, true)))
		exit(1);
    init_player(player);
    game->player = player;
    load_textures(txtr);
    game->ray = r;
}

/*// void init_game(t_map *map_info, t_game *game, t_player *player)
// {
//     if (!(game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, true)))
// 		exit(1);
//     init_player(map_info, player);
//     game->player = player;
//     //load_textures(game);
//     game->map = map_info->temp_map;
//     // test_map(game);
// }

// int gameplay(t_map *map_info, t_txtr *txtr)
// {
//     t_game game;
//     t_player player;

//     game = (t_game){0};
//     player = (t_player){0};
//     init_game(map_info, &game, &player);
//     screen(&game);
//     mlx_loop_hook(game.mlx, keys, &game);
// 	mlx_loop(game.mlx);
// 	mlx_terminate(game.mlx);
//     clean_mem(&game, GAME);
//     clean_mem(txtr, TXTR);
//     // clean_mem(map_info, MAP);
//     // free_test_map(&game);
//     return (0);
// }*/

int gameplay(t_map *map_info, t_txtr *txtr)
{
    static t_game game;
    t_player player;
    t_ray r;

    game = (t_game){0};
    player = (t_player){0};
	  txtr->n_txtr = NULL;
	  txtr->s_txtr = NULL;
	  txtr->w_txtr = NULL;
	  txtr->e_txtr = NULL;
    game.textures = txtr;
    r = (t_ray){0};
    game.map = map_info->temp_map;
    // free_arr(map_info->temp_map);
    init_game(&game, &player, txtr, &r);
    screen(&game);
    mlx_loop_hook(game.mlx, keys, &game);
	  mlx_loop(game.mlx);
	  mlx_terminate(game.mlx);
    clean_mem(&game, GAME);
    clean_mem(txtr, TXTR);
    return (0);
}

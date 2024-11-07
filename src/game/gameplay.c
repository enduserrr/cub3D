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

void	screen(void *param)
{
	t_game	*game;

	game = param;
	if (game->screen)
		mlx_delete_image(game->mlx, game->screen);
	game->screen = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->screen)
	{
		out(game);
		exit(1);
	}
	if (mlx_image_to_window(game->mlx, game->screen, 0, 0) == -1)
	{
		out(game);
		exit(1);
	}
	raycast(game);
	game->screen->instances[0].z = 0;
}

void	keys(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	wasd(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate(game, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate(game, 1);
}

void	get_weapon(t_game *game)
{
	game->textures->gun = mlx_load_png("./textures/gun.png");
	if (!game->textures->gun)
	{
		out(game);
		exit(1);
	}
	game->gun = mlx_new_image(game->mlx, WEAPON_W, WEAPON_H);
	if (!game->gun)
	{
		out(game);
		exit(1);
	}
	game->gun = mlx_texture_to_image(game->mlx, game->textures->gun);
	if (!game->gun)
	{
		out(game);
		exit(1);
	}
	if (mlx_image_to_window(game->mlx, game->gun, WIN_WIDTH / 3, (WIN_HEIGHT
				- WEAPON_H)) == -1)
	{
		out(game);
		exit(1);
	}
	game->gun->instances[0].z = 1;
}

int	gameplay(t_game *game)
{
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, true);
	if (!game->mlx)
		exit(1);
	get_weapon(game);
	mlx_loop_hook(game->mlx, screen, game);
	mlx_loop_hook(game->mlx, keys, game);
	mlx_loop(game->mlx);
	out(game);
	return (0);
}

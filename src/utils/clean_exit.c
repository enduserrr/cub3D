/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:08:13 by eleppala          #+#    #+#             */
/*   Updated: 2024/11/24 10:57:08 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

static void	delete_textures(t_game *game)
{
	if (game->textures->f)
		free(game->textures->f);
	if (game->textures->c)
		free(game->textures->c);
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

static void	delete_images(t_game *game)
{
	if (game->gun)
	{
		mlx_delete_image(game->mlx, game->screen);
	}
	if (game->screen)
	{
		mlx_delete_image(game->mlx, game->screen);
		mlx_close_window(game->mlx);
	}
}

void	out(t_game *game, char *error)
{
	if (game->textures)
		delete_textures(game);
	delete_images(game);
	if (game->mlx)
		mlx_terminate(game->mlx);
	game->textures->f = NULL;
	game->textures->c = NULL;
	free_map(game);
	game->data = NULL;
	game->mlx = NULL;
	game->textures = NULL;
	game->screen = NULL;
	game = NULL;
	if (error)
	{
		write_err(error);
		exit(1);
	}
}
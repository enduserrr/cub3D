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

unsigned char	*get_texture_pixels(t_game *game, int i)
{
	if (i == 1)
		return (game->textures->e_txtr->pixels);
	if (i == 2)
		return (game->textures->w_txtr->pixels);
	if (i == 3)
		return (game->textures->s_txtr->pixels);
	else
		return (game->textures->n_txtr->pixels);
}

unsigned int	get_color(unsigned char *pixels, int text_x, int text_y)
{
	int				tex_y;
	int				tex_x;
	unsigned char	*rgba;

	tex_y = text_y % TXTR_SIZE;
	tex_x = text_x % TXTR_SIZE;
	rgba = pixels + (tex_y * TXTR_SIZE + tex_x) * BYTES_P;
	return ((rgba[0] << 24) | (rgba[1] << 16) | (rgba[2] << 8) | rgba[3]);
}

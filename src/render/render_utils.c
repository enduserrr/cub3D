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

/**
 * @brief 	Retrieves the pixel data of a texture based on the given texture index.
 * @param 	game 	The game structure containing texture data.
 * @param 	i 	The index of the texture (1: East, 2: West, 3: South, others: North).
 * @return 	Pointer to the pixel data of the selected texture.
 * 
 * This function returns a pointer to the pixel data of the texture based on 
 * the provided index. The index corresponds to one of the four cardinal 
 * directions: East, West, South, or North. Each direction has its own texture 
 * stored in the `game->textures` structure.
 */

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

/**
 * @brief 	Retrieves the color from the texture at the given (x, y) coordinates.
 * @param 	pixels 	Pointer to the texture's pixel data.
 * @param 	text_x 	The x-coordinate of the pixel in the texture.
 * @param 	text_y 	The y-coordinate of the pixel in the texture.
 * @return 	The color of the pixel as an unsigned integer in ARGB format.
 * 
 * This function calculates the correct pixel location in the texture based on the provided 
 * (x, y) coordinates and retrieves the color at that location. The pixel data is expected to 
 * be in a format with RGBA channels, and the function returns the color as an unsigned integer 
 * in ARGB format (alpha, red, green, blue).
 */

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

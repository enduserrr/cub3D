/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 07:46:26 by asalo             #+#    #+#             */
/*   Updated: 2024/10/30 07:46:27 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

void	pixel_safe(t_game *game, int x, int y, int color)
{
	if (x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
		return ;
	mlx_put_pixel(game->screen, (uint32_t)x, (uint32_t)y, color);
}

static uint32_t	rgb_to_hex(t_color *color)
{
	int	red;
	int	green;
	int	blue;
	int	a;

	if (!color || color->r > 255 || color->g > 255 || color->b > 255
		|| color->a > 255)
		return (0);
	red = (int)color->r;
	green = (int)color->g;
	blue = (int)color->b;
	a = (int)color->a;
	return ((red << 24) | (green << 16) | (blue << 8) | a);
}

void	textures(t_game *game)
{
	if (game->ray->side == 0)
	{
		if (game->ray->map_x > game->player->ppx)
			game->ray->pixels = get_texture_pixels(game, 1);
		else
			game->ray->pixels = get_texture_pixels(game, 2);
		game->ray->wall_x = game->player->ppy + game->ray->distance
			* game->ray->dir_y;
	}
	else if (game->ray->side == 1)
	{
		if (game->ray->map_y > game->player->ppy)
			game->ray->pixels = get_texture_pixels(game, 3);
		else
			game->ray->pixels = get_texture_pixels(game, 4);
		game->ray->wall_x = game->player->ppx + game->ray->distance
			* game->ray->dir_x;
	}
	game->ray->wall_x -= floor(game->ray->wall_x);
	game->ray->text_x = (int)(game->ray->wall_x * (float)TXTR_SIZE);
	if (game->ray->side == 0 && game->ray->dir_x > 0)
		game->ray->text_x = TXTR_SIZE - game->ray->text_x - 1;
	if (game->ray->side == 1 && game->ray->dir_y < 0)
		game->ray->text_x = TXTR_SIZE - game->ray->text_x - 1;
}

void	background(t_game *game, int i)
{
	int	half;
	int	start;
	int	up;
	int	down;

	up = rgb_to_hex(game->textures->c);
	down = rgb_to_hex(game->textures->f);
	half = WIN_HEIGHT / 2;
	start = 0;
	while (start < half)
	{
		pixel_safe(game, i, start, up);
		start++;
	}
	while (start < WIN_HEIGHT)
	{
		pixel_safe(game, i, start, down);
		start++;
	}
}

void	draw(t_game *game, int i)
{
	int				y;
	int				x;
	double			step;
	double			texture_pos;
	unsigned int	color;

	y = game->ray->draw_start;
	x = game->ray->draw_end;
	step = 1.0 * ((double)TXTR_SIZE) / (double)game->ray->wall_height;
	texture_pos = ((double)game->ray->draw_start - ((double)WIN_HEIGHT / 2.0)
			+ ((double)game->ray->wall_height / 2.0)) * step;
	textures(game);
	background(game, i);
	while (y < x)
	{
		game->ray->text_y = (int)texture_pos & (TXTR_SIZE - 1);
		texture_pos += step;
		color = get_color(game->ray->pixels, game->ray->text_x,
				game->ray->text_y);
		pixel_safe(game, i, y, (uint32_t)color);
		y++;
	}
}

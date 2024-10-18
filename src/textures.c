/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:06:42 by eleppala          #+#    #+#             */
/*   Updated: 2024/10/18 15:06:44 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ei toimi viela, siirsin tanne texture liittyvaa asiaa ennen push, jotta jaa toimiva versio.

/*

void draw_result(t_game *game, float ray_y, float height, int i, float hit_x, int texture_id, int hit_side)
{
    t_texture *texture = &game->textures[texture_id];  // Select the appropriate texture

    float step = (float)texture->height / height;  // How much to step in the texture for each pixel of the wall slice
    float tex_pos = 0;

    if (hit_side == 1)  // If it's a vertical hit, flip the texture coordinate
        hit_x = 1 - hit_x;

    for (int y = 0; y < height; y++)
    {
        int tex_y = (int)tex_pos & (texture->height - 1);  // Get the correct pixel row from the texture
        tex_pos += step;

        int color = texture->pixels[(int)(hit_x * texture->width) + tex_y * texture->width];  // Get pixel from texture

        pixel_safe(game, i, ray_y + y, color);  // Draw the texture pixel onto the wall slice
    }
}







void horizontal_rays(t_game *game, float ray_x, float ray_y, float a, int i)
{
    float height;
    float length;
    float cos_angle = cos(a);
    float sin_angle = sin(a);

    height = 0;
    while(!wall(game, ray_x, ray_y))
    {
        //mlx_put_pixel(game->screen, ray_x, ray_y, 0xFF16FF);
        ray_x += cos_angle;
        ray_y += sin_angle;
        //(void)i;
    }
    //////////////////////////////////////
    int hitside;

    if (fabs(ray_x - floor(ray_x / TILE) * TILE) < fabs(ray_y - floor(ray_y / TILE) * TILE))
        hitside = 0; // Horizontal hit
    else
        hitside = 1; // Vertical hit

    float hit_x;
    if (hitside == 0)
        hit_x = fmod(ray_y, TILE) / TILE;
    else
        hit_x = fmod(ray_x, TILE) / TILE;
    //////////////////////////////////////
    length = ray_length(game, ray_x, ray_y);
    height = (TILE / length) * (WIN_WIDTH / 2);
    ray_y = (WIN_HEIGHT - height) / 2;
    draw_result(game, ray_y, height, i, hit_x, 1, hitside);
}

void load_textures(t_game *game)
{
    int     tex_width;
    int     tex_height;

    game->textures[0].pixels = (int *)mlx_get_data_addr(mlx_xpm_file_to_image(game->mlx, "wall_texture.xpm", &tex_width, &tex_height), &bpp, &size_line, &endian);
    game->textures[0].width = tex_width;
    game->textures[0].height = tex_height;
}
*/
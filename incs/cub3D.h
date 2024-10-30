/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:17:37 by asalo             #+#    #+#             */
/*   Updated: 2024/10/07 10:18:14 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>

# include <math.h>
# include <fcntl.h>
# include "libft/incs/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

# define W      "\033[0;37m"
# define RB     "\033[1;91m"
# define RES    "\033[0m"

# define WIN_WIDTH  1280
# define WIN_HEIGHT 720
# define WIN_NAME   "cub3D"
# define TILE       64
# define TXTR_SIZE  64
# define PI 3.14159265359

typedef struct s_map
{
	char			**temp_map;
    size_t          size_y;
}					t_map;
typedef struct s_txtr
{
    char            **info;
    unsigned int          f;
    unsigned int          c;
    mlx_texture_t   *n_txtr;
    mlx_texture_t   *e_txtr;
    mlx_texture_t   *s_txtr;
    mlx_texture_t   *w_txtr;
} t_txtr;

typedef struct s_player
{
    float       ppx;
    float       ppy;
    float       pa;

} t_player;

typedef struct s_ray
{
    int     index;
    bool    corner;
    float   sx;
    float   sy;
    int     hx;
    int     hy;
    int     hs;
    float   wall_y;
    float   wall_height;
    float   angle;
    double  length;
} t_ray;


typedef struct s_game
{
    mlx_t           *mlx;
    mlx_image_t     *screen;
    t_map           *map_info;
    t_player        *player;
    t_txtr          *textures;
    t_ray           ray[1280];
} t_game;

/* extract.c */
int             get_map(char **av, t_game *game);

/* gameplay.c */
int             gameplay(t_game *game);
void            screen(t_game *window);
void            load_textures(t_txtr *txtr, char **arr);

/* player.c */
void            wasd(t_game *game);
void            rotate(t_game *game);

/* validate.c */
int             process_map(t_game *game);

/* map_info.c */
int             get_info(t_game *game);

/* map_utils.c */
void            set_player(t_game *game, char c, size_t x, size_t y);
char            *ft_strjoin_mod(char const *s1, char const *s2);
int             is_player(char c);
int             validate_file(char *name);

/* draw.c */
void            draw_result(t_game *game, int i);

/* raycasting.c */
void            raycast(t_game *game);

/* hit_side.c*/
void hit_side(t_game *game, int i);

/* render_utils.c */
float           ray_length(t_game *game, float ray_x, float ray_y);
bool            wall(t_game *game, float x, float y);
void            pixel_safe(t_game *win, int x, float y, unsigned int color);
unsigned int    get_color(unsigned char *pixels, int tex_x, float texture_pos);
unsigned char   *get_texture_pixels(t_game *game, int i);

/* utils */
void            free_map(t_game *game);
void            free_arr(char **arr);
void            write_err(char *s);

#endif

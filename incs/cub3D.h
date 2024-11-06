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

# define WIN_WIDTH  960
# define WIN_HEIGHT 720
# define WIN_NAME   "cub3D"
#define  FOV        0.66
# define TILE       64
# define TXTR_SIZE  64
# define PI 3.14159265359

typedef struct s_map
{
	char			**map;
    size_t          size_y;
}					t_map;

typedef struct s_color
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}	t_color;

typedef struct s_txtr
{
    t_color         *f;
    t_color         *c;
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
    float       pax;
    float       pay;
    float       plane_x;
    float       plane_y;

} t_player;

typedef struct s_ray
{
    double          camera_x;
    double          dir_x;
    double          dir_y;
    double          d_dist_x;
    double          d_dist_y;
    double          s_dist_x;
    double          s_dist_y;
    double          distance;
    double          wall_height;
    double          wall_x;
    double          text_x;
    double          text_y;
    int             map_x;
    int             map_y;
    int             step_x;
    int             step_y;
    int             hit;
    int             side;
    int             draw_start;
    int             draw_end;
    unsigned char   *pixels;
} t_ray;

typedef struct s_game
{
    mlx_t           *mlx;
    mlx_image_t     *screen;
    t_map           *map_info;
    t_player        *player;
    t_txtr          *textures;
    t_ray           *ray;
} t_game;

/* extract.c */
int             get_map(char **av, t_game *game);

/* gameplay.c */
int             gameplay(t_game *game);
void            screen(void *param);;

/* player.c */
void            wasd(t_game *game);
void            rotate(t_game *game, int dir);

/* validate.c */
int             process_map(t_game *game);

/* map_info.c */
int             get_info(t_game *game);

/* map_utils.c */
void            set_player(t_game *game, char c, size_t x, size_t y);
int             is_player(char c);
int             validate_file(char *name);

/* draw.c */
void            draw(t_game *game, int i);

/* raycasting.c */
void            raycast(t_game *game);

/* render_utils.c */
void            pixel_safe(t_game *game, int x, int y, int color);
unsigned int    get_color(unsigned char *pixels, int tex_x, int tex_y);
unsigned char   *get_texture_pixels(t_game *game, int i);

/* utils */
void            free_map(t_game *game);
void            free_arr(char **arr);
void            write_err(char *s);
char            *gnl_mod(int fd);
char            *strjoin_mod(char *s1, char *s2, int *line_end);

#endif

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
# define WB     "\033[1;97m"
# define BB     "\033[1;96m"
# define YB     "\033[1;93m"
# define RB     "\033[1;91m"
# define GC     "\033[3;90m"
# define RES    "\033[0m"


//for gameplay.c
# define WIN_WIDTH  1280
# define WIN_HEIGHT 720
# define WIN_NAME   "cub3D"
# define TILE       64
# define PI 3.14159265359

typedef struct s_map
{
	char			**temp_map;
    char            start_orientation;
	size_t          start_position_x;
	size_t			start_position_y;
    size_t          size_x;
    size_t          size_y;
	int				exit;
    // int             ceiling_color;
    // int             floor_color;
    // int             txtr_north;
    // int             txtr_south;
    // int             txtr_east;
    // int             txtr_west;
}					t_map;

typedef struct s_player
{
    float       ppx;    //player position x
    float       ppy;    //player position y
    float       pa;     //player angle

} t_player;

typedef struct s_ray
{
    int   index;
    float sx;
    float sy;
    int   hx;
    int   hy;
    int   hs;
    double length; 
} t_ray;

typedef struct s_texture
{
    mlx_texture_t   *n_txtr;
    mlx_texture_t   *e_txtr;
    mlx_texture_t   *s_txtr;
    mlx_texture_t   *w_txtr;
} t_texture;


typedef struct s_game
{
    mlx_t           *mlx;
    mlx_image_t     *screen;
    t_player        *player;
    t_texture       *textures;
    t_map           *map_info;
    t_ray           *ray;
    char            **map;
    int             map_height;
    int             map_width;
} t_game;


//functions
int gameplay();
void screen(t_game *window);
void load_textures(t_texture *test);
unsigned int get_texture_pixel(mlx_image_t *texture, int x, int y);


//raycasting.c
void raycast(t_game *window);
bool wall(t_game *window, float x, float y);

//draw.c
void pixel_safe(t_game *win, int x, float y, unsigned int color);
void draw_tile(t_game *window, int size, int x, int y);
void draw_map(t_game *window);

//player.c
void init_player(t_player *player);
void draw_player(t_game *game);
void wasd(t_game *game);
void rotate(t_game *game);

//test_map.c  ---  only for debugging and before parsing is finished. Delete later
void test_map(t_game *window);
void free_test_map(t_game *game);

/* Map Utils */
char    *ft_strjoin_mod(char const *s1, char const *s2);
int    	basic_check(t_map *map_info);
int     is_player(char c);
int     is_valid(char c);
void	free_arr(char **arr);
void	exit_error(char *s, int state);
void    write_err(char *s);
// char	*read_fd(int fd);
// void    write_err(char *s);

#endif

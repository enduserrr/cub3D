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

# define WIN_WIDTH  1280
# define WIN_HEIGHT 720
# define WIN_NAME   "cub3D"
# define TILE       64
# define PI 3.14159265359
typedef struct s_map
{
	char			**temp_map;
    size_t          size_y;
}					t_map;
typedef struct s_txtr
{
    char            **info;
    // size_t          *f;
    // size_t          *c;
    mlx_texture_t   *n_txtr;
    mlx_texture_t   *e_txtr;
    mlx_texture_t   *s_txtr;
    mlx_texture_t   *w_txtr;
} t_txtr;

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


typedef struct s_game
{
    mlx_t           *mlx;
    mlx_image_t     *screen;
    t_map           *map_info;
    t_player        *player;
    t_txtr          *textures;
    t_ray           *ray;
} t_game;

// int gameplay(t_map *map_info, t_txtr *txtr);
int             gameplay(t_game *game);
void            screen(t_game *window);
void            load_textures(t_txtr *test);
unsigned char   *get_texture_pixels(t_game *game);



void            raycast(t_game *window);
bool            wall(t_game *window, float x, float y);

void            pixel_safe(t_game *win, int x, float y, unsigned int color);
void            draw_tile(t_game *window, int size, int x, int y);
void            draw_map(t_game *window);

// void init_player(t_map *map_info, t_player *player);
void            init_player(t_game *game);
void            draw_player(t_game *game);
void            wasd(t_game *game);
void            rotate(t_game *game);

void            free_test_map(t_game *game);

char            *ft_strjoin_mod(char const *s1, char const *s2);
void            free_arr(char **arr);
// void	exit_error(char *s, int state);
void            write_err(char *s);
void	        put_arr(char **arr);

int             is_player(char c);
int             is_valid(char c);
// int	    process_map(t_map *map_info);
// int     get_info(t_map *map_info, t_txtr  *txtrs);
int             process_map(t_game *game);
int             get_info(t_game *game);

#endif

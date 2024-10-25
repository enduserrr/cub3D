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

typedef enum e_type
{
    MAP,
    TXTR,
    GAME
}   t_type;
typedef struct s_map
{
	char			**temp_map;
    char            start_orientation;
	size_t          start_position_x;
	size_t			start_position_y;
    size_t          size_x;
    size_t          size_y;
}					t_map;

typedef struct s_txtr
{
    char    **info;
} t_txtr;

typedef struct s_player
{
    float       ppx;    //player position x
    float       ppy;    //player position y
    float       pa;     //player angle
    float       mppx;   //player position on map;
    float       mppy;   //player position on map;

} t_player;

typedef struct s_game
{
    mlx_t           *mlx;
    mlx_image_t     *screen;
    t_player        *player;
    // t_texture       *textures;
    t_map           *map_info;
    char            **map;
    int             map_height;
    int             map_width;
} t_game;


//functions
int gameplay();
void screen(t_game *window);


//raycasting.c
void raycast(t_game *window);
bool wall(t_game *game, int int_ray_x, int int_ray_y);
// bool wall(t_game *game, float x, float y);

//draw.c
void pixel_safe(t_game *win, int x, float y, unsigned int color);
void draw_tile(t_game *window, int size, int x, int y);
void draw_map(t_game *window);

//player.c
// void init_player(t_player *player);
void init_player(t_map *map_info, t_player *player);
// void init_player(t_player *player);
void draw_player(t_game *game);
void wasd(t_game *game);
void rotate(t_game *game);

//test_map.c  ---  only for debugging and before parsing is finished. Delete later
void test_map(t_game *window);
void free_test_map(t_game *game);

/* Map Utils */
char    *ft_strjoin_mod(char const *s1, char const *s2);
void	free_arr(char **arr);
void	exit_error(char *s, int state);
void    write_err(char *s);
void	put_arr(char **arr);

int     is_player(char c);
int     is_valid(char c);
int	    process_map(t_map *map_info);
int     get_info(t_map *map_info, t_txtr  *txtrs);

void    clean_mem(void *ptr, t_type type);

#endif

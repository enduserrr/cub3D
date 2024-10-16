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

#include <math.h>
#include <fcntl.h>
#include "libft/incs/libft.h"
#include "MLX42/include/MLX42/MLX42.h"

# define W      "\033[0;37m"
# define WB     "\033[1;97m"
# define BB     "\033[1;96m"
# define YB     "\033[1;93m"
# define RB     "\033[1;91m"
# define GC     "\033[3;90m"
# define RES    "\033[0m"


//for window
# define WIN_WIDTH  1200
# define WIN_HEIGHT 1200
# define WIN_NAME   "cub3D"

/* for flood_fill */
typedef struct s_point
{
    int x;
    int y;
}   t_point;

/* Used for setting players starting cardinal direction */
typedef enum e_compass
{
    NORTH = 0,
    SOUTH = 1,
    WEST = 2,
    EAST = 3
} t_compass;

typedef struct s_data
{
    char		**map;
	mlx_t		*mlx;
	int			plr_pos_x;
	int			plr_pos_y;
    int			moves_count;
    t_map_info  *map_info;
}				t_data;

typedef struct s_map_info
{
	char        **temp_map;
	int		    start;
	int		    start_position_x;
	int         start_position_y;
    t_compass   start_direction;
	int			exit;
}				t_map_info;


//functions
int window();


#endif

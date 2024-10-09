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
# define CUBED_H

#include <math.h>
#include <fcntl.h>
#include "libft/incs/libft.h"
#include "minilibx/mlx.h"

# define W      "\033[0;37m"
# define WB     "\033[1;97m"
# define BB     "\033[1;96m"
# define YB     "\033[1;93m"
# define RB     "\033[1;91m"
# define GC     "\033[3;90m"
# define RES    "\033[0m"

# define        TXTR_COUNT 10

/* general info for creating the map */
typedef struct s_data
{
    int *txtr_buffer[TXTR_COUNT];
}   t_data;

/* for flood_fill */
typedef struct s_point
{
    int x;
    int y;
}   t_point;

/* Used for setting cardinal direction */
typedef enum e_compass
{
    NORTH = 0,
    SOUTH = 1,
    WEST = 2,
    EAST = 3
} t_compass;

#endif

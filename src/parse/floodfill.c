/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:36:45 by asalo             #+#    #+#             */
/*   Updated: 2024/10/08 11:47:57 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

// typedef struct s_point
// {
//     int x;
//     int y;
// }   t_map;

// void    fill(char **tab, t_map size, t_map i, char c)
// {
//     if (i.size_y < 0 || i.size_y >= size.size_y || i.size_x < 0 || i.size_x >= size.size_x ||
//         tab[i.size_y] != c)
//         return ;
//     tab[i.size_y][i.size_x] = '1';
//     fill(tab, size, (t_map){i.size_x - 1, i.size_y}, c);
//     fill(tab, size, (t_map){i.size_x + 1, i.size_y}, c);
//     fill(tab, size, (t_map){i.size_x, i.size_y - 1}, c);
//     fill(tab, size, (t_map){i.size_x, i.size_y + 1}, c);
// }

// void    flood_fill(char **tab, t_map size, t_map begin)
// {
//     fill(tab, size, begin, tab[begin.size_y][begin.size_x]);
// }


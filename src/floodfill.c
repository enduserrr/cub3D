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

#include "../incs/cub3D.h"

// typedef struct s_point
// {
//     int x;
//     int y;
// }   t_point;

void    fill(char **tab, t_point size, t_point i, char c)
{
    if (i.y < 0 || i.y >= size.y || i.x < 0 || i.x >= size.x ||
        tab[i.y] != c)
        return ;
    tab[i.y][i.x] = '1';
    fill(tab, size, (t_point){i.x - 1, i.y}, c);
    fill(tab, size, (t_point){i.x + 1, i.y}, c);
    fill(tab, size, (t_point){i.x, i.y - 1}, c);
    fill(tab, size, (t_point){i.x, i.y + 1}, c);
}

void    flood_fill(char **tab, t_point size, t_point begin)
{
    fill(tab, size, begin, tab[begin.y][begin.x]);
}

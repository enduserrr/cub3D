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

/*
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

*/
/*int is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

int	is_valid(char c)
{
	if (is_player(c) || c == ' ' || c == '1' || c == '0')
		return (1);
	return (0);
}

int	check_next(char **map, int x, int y)
{
	int	i;

	i = 0;
	if (map[y][x + 1] == 'X' || is_valid(map[y][x + 1]))
		i++;
	if (map[y][x - 1] == 'X' || is_valid(map[y][x - 1]))
		i++;
	if (map[y + 1][x] == 'X' || is_valid(map[y + 1][x]))
		i++;
	if (map[y - 1][x] == 'X' || is_valid(map[y - 1][x]))
		i++;
	return (i);
}

void	check_path(char **map)
{
	size_t	x;
	size_t	y;
	size_t	count;

	x = 0;
	y = 0;
	count = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (is_valid(map[y][x]))
			{
				if (!check_next(map, x, y))
					return (err("map error"), exit(1));
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void	fill(t_map *map_info, size_t x, size_t y)
{
	if ((x < map_info->size_x && y < map_info->size_y) &&
	(map_info->temp_map[y][x] == '0' || ft_isspace(map_info->temp_map[y][x])))
		map_info->temp_map[y][x] = 'X';
	else
		return ;
	fill(map_info, x, (y + 1));
	fill(map_info, x, (y - 1));
	fill(map_info, (x + 1), y);
	fill(map_info, (x - 1), y);
}

void	start_position(t_map *map_info, char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (is_player(map[y][x]))
			{
				map[y][x] = '0';
				map_info->start_position_x = x;
				map_info->start_position_y = y;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void	flood_fill(t_map *map_info, char **map)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	start_position(map_info, map);
	x = map_info->start_position_x;
	y = map_info->start_position_y;
	fill(map_info, x, y);
	check_path(map_info->temp_map);
}*/

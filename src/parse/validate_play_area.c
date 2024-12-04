/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_play_area.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:58:07 by eleppala          #+#    #+#             */
/*   Updated: 2024/12/03 17:58:09 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

void flood_fill(char **s, int x, int y)
{
	if (y < 0 || x < 0 || !s[y] || !s[y][x] || s[y][x] != '0')
		return;
	s[y][x] = 'F';
	flood_fill(s, x, (y + 1));
	flood_fill(s, x, (y - 1));
	flood_fill(s, (x + 1), y);
	flood_fill(s, (x - 1), y);
}

int invalid_player_pos(char **s, int x, int y)
{
	if (x < 1 || y < 1)
		return 1;
	if (((size_t)x + 1) == ft_strlen(s[y]) || y + 1 == arrlen(s))
		return 1;
	return 0;
}
int compare_next(char **s, int x, int y)
{
	if (s[y][x + 1] != '1' && s[y][x + 1] != 'F')	//right side
		return (write_err(ERROR_SPACE), 1);
	if (s[y][x - 1] != '1' && s[y][x - 1] != 'F')	//left side
		return (write_err(ERROR_SPACE), 1);
	if (s[y - 1][x] != '1' && s[y - 1][x] != 'F')	//upside
		return (write_err(ERROR_SPACE), 1);
	if (s[y + 1][x] != '1' && s[y + 1][x] != 'F')	//upside
		return (write_err(ERROR_SPACE), 1);
	return (0);
}

int check_paths(char **s)
{
	int y = 0;
	int x = 0;

	while(s[y])
	{
		while(s[y][x])
		{
			if (s[y][x] == 'F')
			{
				if (compare_next(s, x, y))
					return (1);
			}
			x ++;
		}
		x = 0;
		y ++;
	}
	return (0); 
}
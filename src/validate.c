/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 09:36:45 by asalo             #+#    #+#             */
/*   Updated: 2024/10/17 09:36:49 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

/**
 * @brief	Function to separate map and map info starting from the end of array
 *			to locate the map. After map find N/W/S/E/F/C and their values and
 *			updating correspongind t_map variables.
 *
 *			Function to remove white spaces from map & check for errors in it
 *			and copy it to t_game.
 */

/*Doesn't work and not necessary if map_format checks for first and last char*/
static int	wall_check(char *s, t_map *map_info)
{
	size_t	i;

	i = 0;
	if (s[0] != 49 || (ft_strlen(s) - 1) != 49)
		return (write_err("wall check error"), 1);
	if (map_info->size_x < ft_strlen(s))
		map_info->size_x = ft_strlen(s);
	return (0);
}

static int	rows(char *s, t_map *map_info)
{
	size_t	i;

	i = 0;
	if (s[i] != '1')
		return (1);
	while (s[i])
	{
		// if (wall_check(s, map_info))
		// 	return (1);
		if (is_valid(s[i]))
		{
			if (is_player(s[i]))
				map_info->start_orientation = s[i];
		}
		else
			return (1);
		i++;
	}
	if (s[i - 1] != '1')
		return (1);
	return (0);
}

static int	first_row(char *s, t_map *map_info)
{
	size_t	i;

	i = 0;
	(void)map_info;
	// if (wall_check(s, map_info))
	// 	return (1);
	while (s[i])
	{
		if (s[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

/*Spaces in the beginning swapped into 0s to allow irregularly shaped maps*/
static int map_format(char **s)
{
    int		i;
	int		k;
    char	last;
	int		flag;

	k = 0;
	while (s[k])
	{
		i = 0;
		flag = 0;
		last = '\0';
		while (s[k][i])
		{
			if (s[k][0] != '1')
				return (1);
			if (s[k][i] == ' ' && !flag)
				flag = 1;
			if (!is_player(s[k][i]) && s[k][i] != ' ' && s[k][i] != '0' && s[k][i] != '1')
				return (1);
			else if (is_player(s[k][i]) || s[k][i] == '0' || s[k][i] == '1')
				last = s[k][i];
			if (s[k][i] == ' ' && flag)
				s[k][i] = '0';
			i++;
		}
		k++;
	}
    if (last != '1')
		return (1);
	printf("From map_format:\n%s\n%s\n%s\n", s[0], s[1], s[2]);
	return (0);
}

/*Check to find 0 not covered with 1's*/
int	basic_check(t_map *map_info)
{
	size_t	i;

	i = 0;
	map_info->size_y = 0;
	map_info->size_x = 0;
	printf("From t_map:\n%s\n%s\n%s\n\n", map_info->temp_map[0],
			map_info->temp_map[1], map_info->temp_map[2]);
	if (map_info->temp_map[i])
	{
		if (map_format(map_info->temp_map))
			return (write_err("formatting error"), 1);
		if (first_row(map_info->temp_map[0], map_info))
			return (write_err("first row error"), 1);
		while (map_info->temp_map[i])
		{
			if (rows(map_info->temp_map[i], map_info))
				return (write_err("row error"), 1);
			map_info->size_y++;
			i++;
		}
		if (i > 0 && (wall_check(map_info->temp_map[i - 1], map_info)))
			return (write_err("last row error"), 1);
	}
	return (0);
}

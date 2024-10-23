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

int	only_ones(t_map *map_info)
{
	int	i;
	int	j;

	i = 0;
	printf("%s\n", map_info->temp_map[0]);
	while (map_info->temp_map[0][i])
	{
		if (map_info->temp_map[0][i] != '1')
			return (write_err("invalid first row"), 1);
		i++;
	}
	i = 0;
	j = map_info->size_y - 1;
	printf("%s\n", map_info->temp_map[j]);
	while (map_info->temp_map[j][i])
	{
		if (map_info->temp_map[j][i] != '1')
			return (write_err("invalid last row"), 1);
		i++;
	}
	return (0);
}

/**
 * Checks for correct first and last row, checks the rows end in 1's, swaps spaces to 1's,
 * finds the player starting orientation, updates the x & y map sizes
 *
 * Doesn't update player starting position yet.
 */
static int validate_chars(char **s, t_map *map_info)
{
    int		i;
	int		k;

	k = -1;
	while (s[++k])
	{
		i = -1;
		while (s[k][++i])
		{
			if (!is_player(s[k][i]) && s[k][i] != ' ' && s[k][i] != '0' && s[k][i] != '1')
				return (1);
			if (is_player(s[k][i]))
				map_info->start_orientation = s[k][i];
			if (s[k][i] == ' ')
				s[k][i] = '1';
		}
		if (s[k][i - 1] != '1')
			return (write_err("incorrect map"), 1);
		if (ft_strlen(s[k]) > map_info->size_x)
        	map_info->size_x = i;
		map_info->size_y++;
	}
	if (only_ones(map_info))
		return (1);
	return (0);
}

/*Validate texture files and paths and colors*/
static int check_info(t_map *map_info)
{
	int	fd;
	int	floor;
	int	ceiling;

	fd = 0;
	floor = ft_atoi(map_info->F);
	ceiling = ft_atoi(map_info->C);
    if ((ceiling < 0 || ceiling > 255) || (floor < 0 || floor > 255))
        return (write_err("incorrect color info"), 1);
    // if ((map_info->NO == NULL || (fd = open(map_info->NO, O_RDONLY)) < 0) || close(fd) ||
    //     (map_info->SO == NULL || (fd = open(map_info->SO, O_RDONLY)) < 0) || close(fd) ||
    //     (map_info->WE == NULL || (fd = open(map_info->WE, O_RDONLY)) < 0) || close(fd) ||
    //     (map_info->EA == NULL || (fd = open(map_info->EA, O_RDONLY)) < 0) || close(fd))
    //     return (write_err("unable to open the texture files"), 1);
    return (0);
}

int	validations(t_map *map_info)
{
	map_info->size_y = 0;
	map_info->size_x = 0;
	visual_info(map_info);
	printf("%s\n%s\n%s\n%s\n%s\n%s\n\n",
    map_info->NO,
    map_info->SO,
    map_info->WE,
    map_info->EA,
    map_info->F,
    map_info->C);
	if (check_info(map_info))
		return (1);
	return (validate_chars(map_info->temp_map, map_info));
}

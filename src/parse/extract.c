/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:34:48 by asalo             #+#    #+#             */
/*   Updated: 2024/10/30 11:34:49 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

/**
 * @brief	Read an fd and copy it's contents to new string.
 *			Handles too large files and read() errors gracefully.
 */
static char	*read_fd(int fd)
{
	char	*new;

	new = gnl_mod(fd);
    return (new);
}

int	get_map(char **av, t_game *game)
{
	t_map	*map_info;
	char	*temp_line;
	char	**arr;
	int		fd;
	int		i;

	map_info = malloc(sizeof(t_map));
	map_info->map = NULL;
	game->map_info = map_info;
	temp_line = NULL;
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (write_err("dang"), 1);
	if ((temp_line = read_fd(fd)) == NULL)
	{
		close(fd);
		return (write_err("read error"), 1);
	}
	arr = ft_split_mod(temp_line, '\n');
	game->map_info->map = arr;
	free(temp_line);
	temp_line = NULL;
	if (game->map_info->map == NULL)
		return (write_err("map error 0"), 1);
	i = process_map(game);
	return (free(map_info), i);
}

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
static char	*read_fd(int fd, char *new)
{
    int     bytes_read;
    char    *tmp;
    char    buffer[4096];
	int		total;

    new = NULL;
	total = 0;
    while ((bytes_read = read(fd, buffer, 4095)) > 0)
    {
		total += bytes_read;
		if (total > 2048)
			return (NULL);
        buffer[bytes_read] = '\0';
        tmp = new;
        new = ft_strjoin_mod(tmp, buffer);
        if (!new)
		{
			free(tmp);
            return (NULL);
		}
        free(tmp);
    }
	if (bytes_read == -1)
		return (free(new), NULL);
    return (new);
}

int	get_map(char **av, t_game *game)
{
	t_map	map_info;
	char	*temp_line;
	int		fd;

	map_info = (t_map){0};
	game->map_info = &map_info;
	temp_line = NULL;
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (write_err("dang"), 1);
	if ((temp_line = read_fd(fd, temp_line)) == NULL)
	{
		close(fd);
		return (write_err("read error"), 1);
	}
	game->map_info->temp_map = ft_split(temp_line, '\n');
	free(temp_line);
	if (game->map_info->temp_map == NULL)
		return (free_arr(game->map_info->temp_map), write_err("map error 0"), 1);
	return (process_map(game));
}

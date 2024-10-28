/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:25:30 by asalo             #+#    #+#             */
/*   Updated: 2024/10/08 11:25:50 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

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

static int	get_map(char **av, t_map *map_info)
{
	char	*temp_line;
	int		fd;

	temp_line = NULL;
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (write_err("dang"), 1);
	if ((temp_line = read_fd(fd, temp_line)) == NULL)
	{
		close(fd);
		return (write_err("read error"), 1);
	}
	map_info->temp_map = ft_split(temp_line, '\n');
	free(temp_line);
	if (map_info->temp_map == NULL)
		return (free_arr(map_info->temp_map), write_err("map error 0"), 1);
	return (process_map(map_info));
}

static int validate_file(char *name)
{
    int fd;

    if (!name || ft_strlen(name) < 4 ||
        ft_strcmp(name + (ft_strlen(name) - 4), ".cub"))
        return (write_err("invalid map"), -1);
    fd = open(name, O_RDONLY);
    if (fd < 0)
	{
		close(fd);
		return (write_err("unable to open the map file"), -1);
	}
	close(fd);
    return (fd);
}
/* Map file size limiter */
int	main(int ac, char **av)
{
	static t_map	map_info;
	int				fd;

	if (ac != 2)
        return (write_err("error: invalid argument count"), 1);
	map_info = (t_map){0};
	fd = validate_file(av[1]);
	if (fd < 0)
		exit(1);
	if (get_map(av, &map_info))
		exit(1);
	return(0);
}

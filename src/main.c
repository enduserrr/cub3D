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

static char	*read_fd(int fd)
{
    int     bytes_read;
    char    *new;
    char    *tmp;
    char    buffer[1024];

    new = NULL;
    while ((bytes_read = read(fd, buffer, 1023)) > 0)
    {
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
	{
		free(new);
        return (NULL);
	}
	close(fd);
	printf("From read:\n%s\n", new);
    return (new);
}

static int	get_map(char **av, t_map *map_info)
{
	char	*temp_line;
	int		fd;

	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (write_err("dang"), 1);
	if ((temp_line = read_fd(fd)) == NULL)
		return (write_err("read error"), 1);
	map_info->temp_map = ft_split(temp_line, '\n');
	free(temp_line);
	if (map_info->temp_map == NULL)
		return (write_err("map error 0"), 1);
	basic_check(map_info);
	return (0);
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
        return (exit_error("error: invalid argument count", 1), 1);
	fd = validate_file(av[1]);
	if (fd < 0)
		exit(1);
	if (get_map(av, &map_info))
		exit(1); /*Add a exit protocol later*/
	// gameplay();
	return(0);
}

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

char	*read_fd(int fd)
{
	int		flag;
	char	*str;
	char	*tmp;
	char	buffer[1085];

	str = NULL;
	flag = 1;
	while (flag)
	{
		flag = read(fd, buffer, 1084);
		buffer[flag] = 0;
		tmp = str;
		str = ft_strjoin(tmp, buffer);
	}
	return (str);
}

char	**init_map(char *line, t_map *map_info)
{
	char		**map;
	// char		**map2;
	// t_map	*map_info;

	// map_info = malloc(sizeof(t_map));
	// if (!map_info)
	// 	error_exit("Error\nMalloc error");
	map = ft_split(line, '\n');
	// map2 = ft_split(line, '\n');
	free(line);
	basic_check(map, map_info);
	map_info->temp_map = map;
	// flood_fill(map_info, map2);
	// free_arr(map2);
	// free(map_info);
	return (map);
}

void	read_map(char **av, t_map *map_info, int fd)
{
	char	*temp_line;
	char	*line;
	int		i;

	temp_line = read(fd);
	if (!temp_line)
		return (err("map error"), exit(0));
	line = ft_strjoin("", temp_line);
	while (temp_line)
	{
		if (i == 0)
			free(temp_line);
		temp_line = get_next_line(fd);
		if (temp_line)
			line = ft_strjoin_mod(line, line, temp_line);
		free(temp_line);
		i++;
	}
	basic_check()
	map_info->temp_map = init_map(line, map_info);
	close(fd);
}

int validate_file(char *name)
{
    int fd;

    if (!name || ft_strlen(name) < 4 ||
        ft_strcmp(name + (ft_strlen(name) - 4), ".cub"))
        return (err("invalid map"), -1);
    fd = open(name, O_RDONLY);
    if (fd < 0)
        return (err("unable to open the map file"), -1);
    return (fd);
}

int	main(int ac, char **av)
{
	static t_map	map_info;
	int				fd;

	if (ac != 2)
        return (err("error: invalid argument count"), 1);
	fd = validate_file(av[1]);
	if (fd < 0)
		exit(1);
	read_map(av, &map_info, fd);
	gameplay();
	//exit_cycle(&game);
	//error_exit("exit");
	return(0);
}

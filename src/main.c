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
/*
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


char	**check_map(char *line, t_data *game)
{
	char		**map;
	char		**map2;
	t_map_info	*map_items;

	map_items = malloc(sizeof(t_map_info));
	if (!map_items)
		error_exit("Error\nMalloc error");
	map = ft_split(line, '\n');
	map2 = ft_split(line, '\n');
	free(line);
	basic_check(map, map_items);
	map_items->temp_map = map2;
	flood_fill(map_items, map2);
	free_array(map2);
	free(map_items);
	return (map);
}

void	read_map(char **av, t_data *game)
{
	int		fd;
	char	*temp_line;
	char	*line;
	int		i;

	i = 0;
	if (fd = validate_file(av[1]) < 0)
		return (err("map error"), exit(0));
	temp_line = get_next_line(fd);
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
	game->map = check_map(line, game);
	close(fd);
}*/

int	main() //int ac, char **av
{
	/*
	static t_data	game;
	int				out;

	if (ac != 2)
        return (err("error: invalid argument count"), 1);
	read_map(av, &game);*/
	gameplay();
	//exit_cycle(&game);
	//error_exit("exit");
	return(0);
}

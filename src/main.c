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
}

void	read_map(char **argv, t_data *game)
{
	int		fd1;
	char	*temp_line;
	char	*line;
	int		i;

	i = 0;
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1)
		error_exit("Error\nOpen error");
	temp_line = get_next_line(fd1);
	if (!temp_line)
		error_exit("Error\nMap error");
	line = ft_strjoin("", temp_line);
	while (temp_line != NULL)
	{
		if (i == 0)
			free(temp_line);
		temp_line = get_next_line(fd1);
		if (temp_line != NULL)
			line = ft_strjoin_mod(line, line, temp_line);
		free(temp_line);
		i++;
	}
	// game->map = check_map(line, game);
	close(fd1);
}

void    exit_cycle()
{}


*/
int	main()
{
	
	/*
	t_data	game;

	game = (t_data){0};
    if (ac != 2)
        return (err("error: invalid argument count"), 1);
    if (validate_file(av[1]) < 0)
        exit(1);
	read_map(av, &game);
	// window(&game);
	// free_array(game.map);
	exit_cycle();*/
}

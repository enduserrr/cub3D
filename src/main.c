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

static void	game_ptrs_init(t_game *game)
{
	game->mlx = NULL;
	game->gun = NULL;
	game->data = NULL;
	game->player = NULL;
	game->ray = NULL;
	game->screen = NULL;
	game->textures = NULL;
}

static int	validate_file(char *name)
{
	int	fd;

	if (!name || ft_strlen(name) < 4 || ft_strcmp(name + (ft_strlen(name) - 4),
			".cub"))
		return (write_err(ERROR_MAP_NAME), -1);
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (write_err(ERROR_OPEN), -1);
	}
	close(fd);
	return (fd);
}

int	main(int ac, char **av)
{
	static t_game	game;
	int				fd;

	game = (t_game){0};
	game_ptrs_init(&game);
	if (ac != 2)
		return (write_err(ERROR_ARG), 1);
	fd = validate_file(av[1]);
	if (fd < 0)
		exit(1);
	if (get_map(av, &game))
		exit(1);
	return (0);
}

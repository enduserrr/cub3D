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

int	main(int ac, char **av)
{
	static t_game	game;
	// t_map			map_info;
	int				fd;

	if (ac != 2)
        return (write_err("error: invalid argument count"), 1);
	// game.map_info = &map_info;
	fd = validate_file(av[1]);
	if (fd < 0)
		exit(1);
	if (get_map(av, &game))
		exit(1);
	return(0);
}

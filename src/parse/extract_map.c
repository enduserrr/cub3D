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
 * @brief	Read an fd and copy it's contents to a new string.
 */
static char	*read_fd(char **av)
{
	char	*new;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (write_err(ERROR_OPEN), NULL);
	new = gnl_mod(fd);
	if (!new)
	{
		close(fd);
		return (write_err(ERROR_GNL), NULL);
	}
	close(fd);
	return (new);
}

int	get_map(char **av, t_game *game)
{
	t_map	*info;
	char	*temp_line;
	char	**arr;
	int		i;

	i = 0;
	info = malloc(sizeof(t_map));
	info->map = NULL;
	game->info = info;
	temp_line = NULL;
	temp_line = read_fd(av);
	arr = ft_split(temp_line, '\n');
	game->info->map = arr;
	free(temp_line);
	temp_line = NULL;
	if (game->info->map == NULL)
		return (write_err(ERROR_NO_MAP), 1);
	i = process_info(game);
	return (free(info), i);
}

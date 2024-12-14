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
char	*read_fd(char **av)
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
	t_map	*data;
	char	*temp_line;
	char	**arr;
	int		i;

	i = 0;
	data = malloc(sizeof(t_map));
	if (!data)
		return (1);
	data->map = NULL;
	data->size_y = 0;
	game->data = data;
	temp_line = NULL;
	temp_line = read_fd(av);
	arr = splitter(temp_line, '\n');
	if (!arr)
		return (free(data), free(temp_line), 1);
	game->data->map = arr;
	free(temp_line);
	temp_line = NULL;
	if (game->data->map == NULL)
		return (write_err(ERROR_MAP), 1);
	i = process_data(game);
	return (free(data), i);
}

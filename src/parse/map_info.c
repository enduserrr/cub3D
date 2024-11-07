/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:18:09 by asalo             #+#    #+#             */
/*   Updated: 2024/10/22 13:18:12 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

static void	str_to_color(t_color *ptr, char *line)
{
	char	**colors;

	colors = ft_split(line, ',');
	if (colors && colors[0] && colors[1] && colors[2])
	{
		ptr->r = ft_atoi(colors[0]);
		ptr->g = ft_atoi(colors[1]);
		ptr->b = ft_atoi(colors[2]);
		ptr->a = 255;
	}
	free_arr(colors);
}

static void	check_info(t_game *game, char *line, int i)
{
	t_color	*colors;

	if (!line || (i != 4 && i != 5))
		return ;
	colors = NULL;
	if (i == 4)
	{
		game->textures->f = malloc(sizeof(t_color));
		str_to_color(game->textures->f, line);
	}
	else if (i == 5)
	{
		game->textures->c = malloc(sizeof(t_color));
		str_to_color(game->textures->c, line);
	}
	return ;
}

static void	load_textures(t_game *game, t_txtr *txtr, char *line, int i)
{
	if (!line)
		return ;
	if (i == 0)
		txtr->n_txtr = mlx_load_png(line);
	else if (i == 1)
		txtr->s_txtr = mlx_load_png(line);
	else if (i == 2)
		txtr->w_txtr = mlx_load_png(line);
	else if (i == 3)
		txtr->e_txtr = mlx_load_png(line);
	else if (i == 4 || i == 5)
		check_info(game, line, i);
	free(line);
	line = NULL;
	return ;
}

static char	*parse_info(char *line, char *result)
{
	int	i;

	while (ft_isspace(*line))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
	{
		i = 3;
		while (ft_isspace(line[i]))
			i++;
		line += i;
		result = ft_strdup(line);
		return (result);
	}
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
	{
		i = 2;
		while (ft_isspace(line[i]))
			i++;
		line += i;
		result = ft_strdup(line);
		return (result);
	}
	return (NULL);
}

/**
 * @brief   Extract color and texture info from file and delete them from map.
 *          Add func to put info straight into mlx_ strings and int array
 *          (with rgb->hex conversion)
 */
int	get_info(t_game *game)
{
	int		i;
	int		k;
	char	**tmp;
	char	*line;

	line = NULL;
	tmp = game->info->map;
	k = 0;
	while (tmp[k])
	{
		line = parse_info(tmp[k], line);
		if (line == NULL)
			break ;
		load_textures(game, game->textures, line, k);
		free(tmp[k]);
		tmp[k] = NULL;
		k++;
	}
	i = 0;
	while (tmp[k])
		tmp[i++] = tmp[k++];
	tmp[i] = NULL;
	game->info->map = tmp;
	return (0);
}

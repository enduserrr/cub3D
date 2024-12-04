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

/**
 * @brief	Converts a comma-separated string into an RGB color.
 * @param	ptr     Pointer to the t_color struct where the values are stored.
 * @param	line    Comma-separated string representing the color values.
 */
void	str_to_color(t_color *ptr, char *line)
{
	char	**colors;
	int		tmp;
	int		i;

	colors = ft_split(line, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2])
	{
		set_inval_color(ptr);
		free_arr(colors);
		return ;
	}
	i = -1;
	while (colors[++i])
	{
		if (i == 3)
		{
			set_inval_color(ptr);
			free_arr(colors);
			return ;
		}
	}
	i = -1;
	while (++i < 3)
	{
		tmp = atoi_mod(colors[i]);
		if (tmp == -1)
			tmp = 256;
		if (i == 0)
			ptr->r = (unsigned int)tmp;
		else if (i == 1)
			ptr->g = (unsigned int)tmp;
		else if (i == 2)
			ptr->b = (unsigned int)tmp;
	}
	free_arr(colors);
}

/**
 * @brief	Extracts floor & ceiling color information from a line.
 * @param	game    Pointer to the t_game struct containing texture data.
 * @param	line    Input string to parse for color information.
 * @return	Pointer to the remaining part of the line if not processed,
 *			or NULL otherwise.
 */
char	*colors(t_game *game, char *line)
{
	while (ft_isspace(*line))
		line++;
	if (ft_strncmp(line, "F ", 2) == 0 && !game->textures->f)
	{
		line += 2;
		while (ft_isspace(*line))
			line++;
		game->textures->f = malloc(sizeof(t_color));
		if (!game->textures->f)
			return (line);
		str_to_color(game->textures->f, line);
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && !game->textures->c)
	{
		line += 2;
		while (ft_isspace(*line))
			line++;
		game->textures->c = malloc(sizeof(t_color));
		if (!game->textures->c)
			return (line);
		str_to_color(game->textures->c, line);
	}
	else
		return (line);
	return (NULL);
}


mlx_texture_t	*put_png(mlx_texture_t *ptr, char *png, t_game *game)
{
	ptr = mlx_load_png(png);
	if (ptr == NULL)
	{
		out(game, ERROR_PNG);
		return (NULL);
	}
	game->textures->txtr_count++;
	return (ptr);
}

/**
 * @brief   Parses texture and color data from a line.
 * @param   game    Pointer to the t_game struct.
 * @param   line    String where the texture & color info are extracted from
 * @return  Pointer to the unprocessed part of the line if parsing fails,
 *			or NULL otherwise.
 *
 * Identifies texture paths (NO, SO, WE, EA) and assigns them to
 * texture fields.
 */
char	*parse_info(t_game *game, char *line)
{
	int		i;
	char	*new;

	new = NULL;
	while (ft_isspace(*line))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
	{
		i = 3;
		while (ft_isspace(line[i]))
			i++;
		new = ft_strdup(line + i);
		if (ft_strncmp(line, "NO ", 3) == 0 && !game->textures->n_txtr)
			game->textures->n_txtr = put_png(game->textures->n_txtr, new, game);
		else if (ft_strncmp(line, "SO ", 3) == 0 && !game->textures->s_txtr)
			game->textures->s_txtr = put_png(game->textures->s_txtr, new, game);
		else if (ft_strncmp(line, "WE ", 3) == 0 && !game->textures->w_txtr)
			game->textures->w_txtr = put_png(game->textures->w_txtr, new, game);
		else if (ft_strncmp(line, "EA ", 3) == 0 && !game->textures->e_txtr)
			game->textures->e_txtr = put_png(game->textures->e_txtr, new, game);
		else
			game->textures->dup = true;
	}
	else if (colors(game, line) != NULL)
		return (line);
	return (free(new), NULL);
}

/**
 * @brief	Processes and removes texture and color info from the map array.
 * @return  0 on success, or an error code if processing fails.
 */
// char	*colors(t_game *game, char *line, int start, int end)
// {
// 	while (ft_isspace(*line))
// 		line++;
// 	if (ft_strncmp(line, "F ", 2) == 0 && !game->textures->f)
// 	{
// 		line += 2;
// 		while (ft_isspace(*line))
// 			line++;
// 		game->textures->f = malloc(sizeof(t_color));
// 		if (!game->textures->f)
// 			return (line);
// 		str_to_color(game->textures->f, line);
// 	}
// 	else if (ft_strncmp(line, "C ", 2) == 0 && !game->textures->c)
// 	{
// 		line += 2;
// 		while (ft_isspace(*line))
// 			line++;
// 		game->textures->c = malloc(sizeof(t_color));
// 		if (!game->textures->c)
// 			return (line);
// 		str_to_color(game->textures->c, line);
// 	}
// 	else
// 		return (line);
// 	game->textures->color_count++;// add
// 	return (NULL);
// }

// mlx_texture_t	*put_png(mlx_texture_t *ptr, char *png, t_game *game)
// {
// 	ptr = mlx_load_png(png);
// 	if (ptr == NULL)
// 	{
// 		free(png);// add
// 		out(game, ERROR_PNG);
// 		return (NULL);
// 	}
// 	game->textures->txtr_count++;
// 	free(png);// add
// 	return (ptr);
// }

// void	*put_data(t_game *game, char *s, int start, int end)
// {
// 	char	*new;

// 	new = NULL;
// 	new = ft_substr(s, (size_t)start, (size_t)(end - start));
// 	if (!new)
// 		return (NULL);
// 	if (ft_strncmp(s, "NO ", 3) == 0 && !game->textures->n_txtr)
// 		return (game->textures->n_txtr = put_png(game->textures->n_txtr, new, game));
// 	else if (ft_strncmp(s, "SO ", 3) == 0 && !game->textures->s_txtr)
// 		return (game->textures->s_txtr = put_png(game->textures->s_txtr, new, game));
// 	else if (ft_strncmp(s, "WE ", 3) == 0 && !game->textures->w_txtr)
// 		return (game->textures->w_txtr = put_png(game->textures->w_txtr, new, game));
// 	else if (ft_strncmp(s, "EA ", 3) == 0 && !game->textures->e_txtr)
// 		return (game->textures->e_txtr = put_png(game->textures->e_txtr, new, game));
// 	else
// 		return (NULL);
// }

// int fetch_data(t_game *game, char *s)
// {
// 	int	i;
// 	int	start;
// 	int	end;

// 	i = 0;
// 	if (!s || !*s)
// 		return (1);
// 	while (s[i])
// 	{
// 		if (game->textures->txtr_count == 4
// 			&& game->textures->color_count == 2)
// 			break ;
// 		start = 0;
// 		end = 0;
// 		if (ft_isspace(s[i]))
// 			i++;
// 		if (ft_strncmp(s[i], "NO ", 3) == 0 || ft_strncmp(s[i], "SO ", 3) == 0
// 		|| ft_strncmp(s[i], "WE ", 3) == 0 || ft_strncmp(s[i], "EA ", 3) == 0)
// 		{
// 			start = i + 3;
// 			while (ft_isspace(s[start]))
// 				start++;
// 			end = start;
// 			while (!ft_isspace(s[end]))
// 				end++;
// 			put_data(game, s, start, end);
// 		}
// 		else if (ft_strncmp(s[i], "F ", 2) || ft_strncmp(s[i], "C ", 2))
// 			colors(game, s, start, end);
// 		i++;
// 	}
// }


int	get_data(t_game *game)
{
	int		i;
	int		k;
	char	**tmp;
	char	*line;

	line = NULL;
	tmp = game->data->map;
	k = 0;
	while (tmp[k])
	{
		line = parse_info(game, tmp[k]);
		if (line != NULL)
			break ;
		free(tmp[k]);
		tmp[k] = NULL;
		k++;
	}
	i = 0;
	while (tmp[k])
		tmp[i++] = tmp[k++];
	tmp[i] = NULL;
	game->data->map = tmp;
	return (0);
}

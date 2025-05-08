#include "../../incs/cub3D.h"

mlx_texture_t	*put_png(mlx_texture_t *ptr, char *png, t_game *game)
{
	size_t	k;
	char	*new;

	k = ft_strplen(png) - 1;
	while (k > 0 && (png[k] == ' ' || png[k] == '\t'))
		k--;
	new = ft_substr(png, 0, k + 1);
	if (!new)
	{
		game->textures->txtr_err++;
		return (NULL);
	}
	ptr = mlx_load_png(new);
	free(new);
	if (ptr == NULL)
	{
		game->textures->txtr_err++;
		return (NULL);
	}
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
char	*parse_info(t_game *game, char *line, int i)
{
	char	*new;

	new = NULL;
	while (ft_isspace(*line))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
	{
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

static int	skip_whitespace_lines(char **arr, int k)
{
	int	i;

	while (arr[k])
	{
		i = 0;
		while (arr[k][i])
		{
			if (!ft_isspace(arr[k][i]))
				return (k);
			i++;
		}
		free(arr[k]);
		arr[k] = NULL;
		k++;
	}
	return (k);
}

int	get_data(t_game *game)
{
	int		i;
	int		k;
	char	**tmp;
	char	*line;

	tmp = game->data->map;
	k = skip_whitespace_lines(tmp, 0);
	while (tmp[k])
	{
		line = parse_info(game, tmp[k], 3);
		if (line != NULL)
			break ;
		free(tmp[k]);
		tmp[k] = NULL;
		k = skip_whitespace_lines(tmp, k + 1);
	}
	k = skip_whitespace_lines(tmp, k);
	i = 0;
	while (tmp[k])
		tmp[i++] = tmp[k++];
	tmp[i] = NULL;
	game->data->map = tmp;
	return (game->textures->txtr_err != 0);
}
